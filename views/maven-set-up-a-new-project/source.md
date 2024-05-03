# Maven set up a new project
2024-05-03 08:37:10 #dev #tools #post
## Install maven
```sh
sudo apt install maven
```

## Create a new project
```sh
mvn archetype:generate\
    -DgroupId=com.test.app\
    -DartifactId=app\
    -DarchetypeArtifactId=maven-archetype-quickstart\
    -DarchetypeVersion=1.4\
    -DinteractiveMode=false

cd app/
```

## Set compiler release
Open the `pom.xml` file and update the following lines:
```xml
<!-- E.g., 11, 17, 21, etc. -->
<maven.compiler.source>21</maven.compiler.source>
<maven.compiler.target>21</maven.compiler.target>
```

## Add dependencies
Add the following sample dependency to the `pom.xml` file:
```xml
<dependencies>
  ...
  <dependency>
    <groupId>com.amazonaws</groupId>
    <artifactId>aws-java-sdk</artifactId>
    <version>1.12.713</version>
  </dependency>
</dependencies>
```

## Package and run
```sh
mvn package
java -cp target/app-1.0-SNAPSHOT.jar com.test.app.App
```
