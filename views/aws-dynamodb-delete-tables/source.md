# DynamoDB: Delete tables
I found myself deleting tables manually from the DynamoDB UI and it started to get tedious. Here a small working program to delete tables in Java:
```java
import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
import com.amazonaws.services.dynamodbv2.document.DynamoDB;
import com.amazonaws.services.dynamodbv2.document.Table;

import com.amazonaws.auth.AWSCredentials;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;

/**
 * Delete a list of tables, handy in testing and debugging.
 *
 * Credentials are read from ~/.aws/credentials.
 * See http://docs.aws.amazon.com/sdk-for-java/v1/developer-guide/setup-credentials.html for more
 * details.
 */
public class TableReaper {
    private DynamoDB db;

    public TableReaper(DynamoDB db) {
        this.db = db;
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.printf("Usage: java DeleteTables <table1> <table2> ... <tableN>");
            System.exit(1);
        }
        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard()
            .withCredentials(new ProfileCredentialsProvider())
            .withRegion(Regions.US_WEST_2)
            .build();
        DynamoDB db = new DynamoDB(client);
        new TableReaper(db).deleteTables(args);
    }

    public void deleteTables(String[] tableNames) {
        try {
            for (String tableName : tableNames) {
                deleteTable(tableName);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void deleteTable(String tableName) {
        Table table = db.getTable(tableName);
        try {
            System.out.printf("Deleting table %s...", tableName);
            table.delete();
            table.waitForDelete();
            System.out.printf(" done!\n");

        } catch (Exception e) {
            System.err.printf("Failed to delete table %s", tableName);
            e.printStackTrace();
        }
    }
}
```

See [maven-getting-started](/maven-getting-started) to learn how to set up a project and the AWS SDK.

## Full source code
You can find the full program at [aws-dynamodb-delete-tables](https://github.com/rendon/code-samples/tree/master/aws-dynamodb-delete-tables).

Run as follows:
```sh
mvn clean package
java -jar target/ddb-1.0-SNAPSHOT-shaded.jar
```
