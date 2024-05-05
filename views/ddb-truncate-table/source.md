# Truncate DynamoDB table
2024-05-04 14:34:22 #dev #aws #post

One of the features that I miss from most RDBMS is the ability to easily delete all rows, either via `DELETE * FROM MyTable` or using `TRUNCATE TABLE MyTable`. Unfortunately, DynamoDB does not have such a feature, you have to either, delete your table or remove all items one at a time.

See [ddb-delete-tables](/ddb-delete-tables) if you want to know how to delete tables using the AWS SDK with Java.

Sometimes however, deleting your tables is not convenient, for example, you will have to define your schema and specify your capacity settings again, in this case, and if your tables contains just a few tens of records, it's easier to remove them one by one.

```java
public class App {
    private DynamoDB db;

    public App(DynamoDB db) {
        this.db = db;
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.printf("Usage: java App <table:partition_key[:sort_key]>\n");
            System.exit(1);
        }
        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard()
            .withCredentials(new ProfileCredentialsProvider())
            .withRegion(Regions.US_WEST_2)
            .build();
        DynamoDB db = new DynamoDB(client);
        new App(db).truncateTable(args[0]);
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

    private void truncateTable(String tableName, String partitionKeyName, String sortKeyName) throws Exception {
        Table table = db.getTable(tableName);
        ScanSpec spec = new ScanSpec();
        ItemCollection<ScanOutcome> items = table.scan(spec);
        Iterator<Item> it = items.iterator();
        while (it.hasNext()) {
            Item item = it.next();
            String partitionKey = item.getString(partitionKeyName);
            String sortKey = item.getString(sortKeyName);
            PrimaryKey key = new PrimaryKey( partitionKeyName, partitionKey, sortKeyName, sortKey);
            table.deleteItem(key);
            System.out.printf("Deleted item with key: <%s, %s>\n", partitionKey, sortKey);
        }
    }

    private void truncateTable(String tableName, String partitionKeyName) throws Exception {
        Table table = db.getTable(tableName);
        ScanSpec spec = new ScanSpec();
        ItemCollection<ScanOutcome> items = table.scan(spec);
        Iterator<Item> it = items.iterator();
        while (it.hasNext()) {
            Item item = it.next();
            String partitionKey = item.getString(partitionKeyName);
            PrimaryKey key = new PrimaryKey(partitionKeyName, partitionKey);
            table.deleteItem(key);
            System.out.printf("Deleted item with key: %s\n", partitionKey);
        }
    }
}
```

## Full source code
The full program is at [ddb-truncate-table](https://github.com/rendon/code-samples/tree/master/ddb-truncate-table).
```sh
mvn package
```

You need to provide the name of your partition key and the sort key if your table has one, for example:
```sh
java -jar target/ddb-1.0-SNAPSHOT-shaded.jar test-table:key:sort
```
