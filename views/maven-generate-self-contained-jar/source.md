# Maven generate self-contained jar
2024-05-03 17:17:33 #dev #post

If your application is meant to run out of the box, it's convenient for the users to get a single file and just execute it. For that, we need a way to bundle everything together in a big JAR file
The [Shade](https://maven.apache.org/plugins/maven-shade-plugin/index.html) plugin can do just that.

**NOTES**:

- Make sure the plugin is directly under `<build>`, not under `<pluginManagement>` or other element.
- Update the `<mainClass>` element accordingly

 Add something like the following to your `<build>` section (within the `pom.xml` file):

```
    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-shade-plugin</artifactId>
                <executions>
                    <execution>
                        <goals>
                            <goal>shade</goal>
                        </goals>
                        <configuration>
                            <shadedArtifactAttached>true</shadedArtifactAttached>
                            <transformers>
                                <transformer implementation="org.apache.maven.plugins.shade.resource.ManifestResourceTransformer">
                                    <mainClass>com.myapp.App</mainClass>
                                </transformer>
                            </transformers>

                            <artifactSet>
                                <excludes>
                                    <exclude>classworlds:classworlds</exclude>
                                    <exclude>junit:junit</exclude>
                                    <exclude>jmock:*</exclude>
                                    <exclude>*:xml-apis</exclude>
                                    <exclude>org.apache.maven:lib:tests</exclude>
                                    <exclude>log4j:log4j:jar:</exclude>
                                </excludes>
                            </artifactSet>

                        </configuration>
                    </execution>
                </executions>
            </plugin>
```

Then build your package as usual (`mvn clean package`). The self-contained jar should be in the `target/` directory with a name like `myapp-1.0-SNAPSHOT-shaded.jar`.

