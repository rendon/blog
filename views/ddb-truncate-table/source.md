# Truncate DynamoDB table
2024-05-04 14:34:22 #dev #aws #post

One of the features that I miss from most RDBMS is the ability to easily delete all rows, either via `DELETE * FROM MyTable` or using `TRUNCATE TABLE MyTable`. Unfortunately, DynamoDB does not have such a feature, you have to either, delete your table or remove all items one at a time.

See [ddb-delete-tables](/ddb-delete-tables) if you want to know how to delete tables using the AWS SDK with Java.

Sometimes however, deleting your tables is not convenient, for example, you will have to define your schema and specify your capacity settings again, in this case, and if your tables contains just a few tens of records, it's easier to remove them one by one.

```java
import java.util.Iterator;

import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
import com.amazonaws.services.dynamodbv2.document.DynamoDB;
import com.amazonaws.services.dynamodbv2.document.Table;
import com.amazonaws.services.dynamodbv2.document.spec.ScanSpec;
import com.amazonaws.services.dynamodbv2.document.ItemCollection;
import com.amazonaws.services.dynamodbv2.document.ScanOutcome;
import com.amazonaws.services.dynamodbv2.document.Item;
import com.amazonaws.services.dynamodbv2.document.PrimaryKey;

import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Regions;

/**
 * Truncates table, handy in testing and debugging.
 *
 * Credentials are read from ~/.aws/credentials.
 * See http://docs.aws.amazon.com/sdk-for-java/v1/developer-guide/setup-credentials.html for more
 * details.
 */
public class TableCleaner {
    private DynamoDB db;

    public TableCleaner(DynamoDB db) {
        this.db = db;
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.printf("Usage: java TableCleaner <table:partition_key[:range_key]>");
            System.exit(1);
        }
        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard()
            .withCredentials(new ProfileCredentialsProvider())
            .withRegion(Regions.US_WEST_2)
            .build();
        DynamoDB db = new DynamoDB(client);
        new TableCleaner(db).truncateTable(args[0]);
    }

    public void truncateTable(String tableSpec) {
        try {
            String[] tokens = tableSpec.split(":");
            if (tokens.length == 2) {
                truncateTable(tokens[0], tokens[1]);
            } else if (tokens.length == 3) {
                truncateTable(tokens[0], tokens[1], tokens[2]);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void truncateTable(String tableName, String hashKeyName, String rangeKeyName) throws Exception {
        Table table = db.getTable(tableName);
        ScanSpec spec = new ScanSpec();
        ItemCollection<ScanOutcome> items = table.scan(spec);
        Iterator<Item> it = items.iterator();
        while (it.hasNext()) {
            Item item = it.next();
            String hashKey = item.getString(hashKeyName);
            String rangeKey = item.getString(rangeKeyName);
            PrimaryKey key = new PrimaryKey( hashKeyName, hashKey, rangeKeyName, rangeKey);
            table.deleteItem(key);
            System.out.printf("Deleted item with key: <%s, %s>\n", hashKey, rangeKey);
        }
    }

    private void truncateTable(String tableName, String hashKeyName) throws Exception {
        Table table = db.getTable(tableName);
        ScanSpec spec = new ScanSpec();
        ItemCollection<ScanOutcome> items = table.scan(spec);
        Iterator<Item> it = items.iterator();
        while (it.hasNext()) {
            Item item = it.next();
            String hashKey = item.getString(hashKeyName);
            PrimaryKey key = new PrimaryKey(hashKeyName, hashKey);
            table.deleteItem(key);
            System.out.printf("Deleted item with key: %s\n", hashKey);
        }
    }
}
```

<!-- TODO: Explain how to set up the SDK to compile the program properly.  -->
Compile
```sh

```

You need to provide the name of your partition key and the range key if your table has one, for example:
```sh
java TableCleaner MyTable:PartionKeyName:RangeKeyName
```
