---
tags:
    - dev
    - aws
    - post
created: 2017-05-02
updated: 2024-05-04
---
# DynamoDB: Delete tables

I found myself deleting tables manually from the DynamoDB UI and it started to get tedious. Here a small working program to delete tables in Java:
```java
public class App {
    private DynamoDB db;

    public App(DynamoDB db) {
        this.db = db;
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.printf("Usage: java App <table1> <table2> ... <tableN>\n");
            System.exit(1);
        }
        AmazonDynamoDB client = AmazonDynamoDBClientBuilder.standard()
            .withCredentials(new ProfileCredentialsProvider())
            .withRegion(Regions.US_WEST_2)
            .build();
        DynamoDB db = new DynamoDB(client);
        new App(db).deleteTables(args);
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

See [[maven-getting-started]] to learn how to set up a project and the AWS SDK.

## Full source code
You can find the full program at [ddb-delete-tables](https://github.com/rendon/code-samples/tree/master/ddb-delete-tables).

Run as follows:
```sh
mvn clean package
java -jar target/ddb-1.0-SNAPSHOT-shaded.jar
```
