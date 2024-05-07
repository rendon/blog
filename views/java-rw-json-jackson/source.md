# Read and write JSON documents in Java with Jackson
2016-02-18 2024-05-07 #dev #java #post

I'm working on my [graph tool](https://github.com/rendon/graph_illustrator/) and I just changed the file format to JSON, then the need to read and write JSON from and to a file.

What I needed was a lightweight library to parse and export JSON content, nothing fancy ... wait, with support for pretty printing, please. I ended up with Jackson, not exactly lightweight, but it did the job.

There are many libraries for this task, [json-simple](https://code.google.com/p/json-simple/), [Google Gson](https://code.google.com/p/google-gson/), [Jackson](http://jackson.codehaus.org/), to name a few. My first try was with json-simple, it's okay, but it lacks of pretty printing. I din't spend too much time on Gson, but it seems that is more suited to map JSON data to classes (and conversely). Jackson was tedious to set up because I had to guess what jar file to use, jackson-core, maybe jackson-databind, jackson-annotations, or all of them! I stayed with Jackson because the **Tree Model** seemed very convenient to read, and indeed it is.

Enough chitchat. Here is the input file that we'll parse:


```json
{
    "Graph": {
        "Edges": [
            {
                "center": {
                    "x": -6.516290726817042,
                    "y": 1.8379281537176269
                },
                "end": 2,
                "label": "10",
                "labelColor": "0x000000ff",
                "start": 1,
                "strokeColor": "0x000000ff",
                "strokeSize": 1.0
            },
            {
                "center": {
                    "x": 0.4594820384294058,
                    "y": 6.265664160401002
                },
                "end": 3,
                "label": "5",
                "labelColor": "0x000000ff",
                "start": 1,
                "strokeColor": "0x000000ff",
                "strokeSize": 1.0
            },
            {
                "center": {
                    "x": 1.0860484544695055,
                    "y": -1.4619883040935668
                },
                "end": 2,
                "label": "7",
                "labelColor": "0x000000ff",
                "start": 3,
                "strokeColor": "0x000000ff",
                "strokeSize": 1.0
            }
        ],
        "Vertices": [
            {
                "backgroundColor": "0x006699ff",
                "borderColor": "0xffffff00",
                "center": {
                    "x": -7.142857142857142,
                    "y": 9.064327485380117
                },
                "key": 1,
                "label": "A",
                "labelColor": "0xffffffff",
                "radius": 1.42879125952273
            },
            {
                "backgroundColor": "0x006699ff",
                "borderColor": "0xffffff00",
                "center": {
                    "x": -5.889724310776942,
                    "y": -6.390977443609022
                },
                "key": 2,
                "label": "B",
                "labelColor": "0xffffffff",
                "radius": 1.42879125952273
            },
            {
                "backgroundColor": "0x006699ff",
                "borderColor": "0xffffff00",
                "center": {
                    "x": 8.061821219715952,
                    "y": 2.4644945697577283
                },
                "key": 3,
                "label": "C",
                "labelColor": "0xffffffff",
                "radius": 1.4287912595227292
            }
        ]
    }
}

```

And here is the code I used to parse it:


```java
import java.io.*;
import java.util.Iterator;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.core.JsonFactory;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonEncoding;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.databind.node.ObjectNode;
import com.fasterxml.jackson.databind.exc.InvalidFormatException;
import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;

public class TestJsonRead {
    public static void readJson() throws InvalidFormatException, IOException
    {
        String fileName = "input.json"; // in the current working directory
        File input = new File(fileName);
        ObjectMapper mapper = new ObjectMapper();
        JsonNode root = mapper.readTree(input);
        Iterator<JsonNode> V = root.path("Graph").path("Vertices").elements();
        while (V.hasNext()) {
            System.out.println("=== Start vertex ===");
            JsonNode v = V.next();
            if (v.get("key") == null || v.get("label") == null) {
                throw new InvalidFormatException(
                            "Vertex's key and label are not optional.",
                            null, null, null
                        );
            }

            Integer key = v.path("key").asInt();
            String label = v.path("label").textValue();

            if (v.get("center") != null) {
                JsonNode point = v.get("center");
                if (point.get("x") != null && point.get("y") != null) {
                    double x = point.get("x").asDouble();
                    double y = point.get("y").asDouble();
                    System.out.printf("Center = (%f, %f)\n", x, y);
                }
            }

            if (v.get("radius") != null) {
                Double radius = v.get("radius").asDouble();
                System.out.println("Radius = " + radius);
            }

            if (v.get("labelColor") != null) {
                String hex = v.get("labelColor").textValue();
                System.out.println("Label color = " + hex);
            }

            if (v.get("backgroundColor") != null) {
                String hex = v.get("backgroundColor").textValue();
                System.out.println("Background color = " + hex);
            }

            if (v.get("borderColor") != null) {
                String hex = v.get("borderColor").textValue();
                System.out.println("Border color = " + hex);
            }

            System.out.println();
        }

        Iterator<JsonNode> E = root.get("Graph").get("Edges").elements();
        while (E.hasNext()) {
            JsonNode e = E.next();
            System.out.println("=== Start edge ===");
            if (e.get("start") == null || e.get("end") == null) {
                throw new InvalidFormatException(
                            "start and end are not optional.",
                            null, null, null
                        );
            }

            Integer start = e.get("start").asInt();
            Integer end = e.get("end").asInt();
            System.out.println("start = " + start);
            System.out.println("end = " + end);

            if (e.get("label") != null) {
                String label = e.get("label").textValue();
                System.out.println("label = " + label);
            }

            if (e.get("labelColor") != null) {
                String hex = e.get("labelColor").textValue();
                System.out.println("label color = " + hex);
            }

            if (e.get("strokeColor") != null) {
                String hex = e.get("strokeColor").textValue();
                System.out.println("stroke color = " + hex);
            }

            if (e.get("strokeSize") != null) {
                String str = e.get("strokeSize").toString();
                System.out.println("stroke size = " + str);
            }

            if (e.get("center") != null) {
                JsonNode point = e.get("center");
                if (point.get("x") != null && point.get("y") != null) {
                    double x = point.get("x").asDouble();
                    double y = point.get("y").asDouble();
                    System.out.printf("center = (%f, %f)\n", x, y);
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args)
    {
        try {
            readJson();
        } catch (InvalidFormatException ife) {
            System.out.println("Error: " + ife.getMessage());
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }
}

```

Compile and run with:


```sh
javac -cp .:jackson-annotations-2.4.0.jar:jackson-core-2.4.0.jar:jackson-databind-2.4.0.jar TestJsonRead.java
java -cp .:jackson-annotations-2.4.0.jar:jackson-core-2.4.0.jar:jackson-databind-2.4.0.jar TestJsonRead

```

Download the Jars from [http://repo1.maven.org/maven2/com/fasterxml/jackson/core/](http://repo1.maven.org/maven2/com/fasterxml/jackson/core/) or use Google to find them.

Actually I don't just read the data and print it out, but store it in some data structures. Here's how the writing looks like:


```java
private void saveToGi() throws JsonGenerationException, IOException
{
    Map<Integer, Vertex> graph = plane.getGraph();
    JsonFactory factory = new JsonFactory();
    File output = new File(fileName);
    JsonGenerator generator = factory.createGenerator(
                output,
                JsonEncoding.UTF8
            );

    // Basic Pretty print
    generator.setPrettyPrinter(new DefaultPrettyPrinter());

    generator.writeStartObject();
    generator.writeFieldName("Graph");
    generator.writeStartObject();
    generator.writeFieldName("Vertices");
    generator.writeStartArray();
    for (Entry<Integer, Vertex> entry : graph.entrySet()) {
        Vertex v = entry.getValue();
        String hexLabelColor = encode(v.getLabelColor());
        String hexBorderColor = encode(v.getBorderColor());
        String hexBackgroundColor = encode(v.getBackgroundColor());
        generator.writeStartObject();
        generator.writeNumberField("key", v.getKey());
        generator.writeStringField("label", v.getLabel());
        generator.writeNumberField("radius", v.getRadius());
        generator.writeStringField("labelColor", hexLabelColor);
        generator.writeStringField("backgroundColor", hexBackgroundColor);
        generator.writeStringField("borderColor", hexBorderColor);

        generator.writeFieldName("center");
        generator.writeStartObject();
        generator.writeNumberField("x", v.getCenter().x());
        generator.writeNumberField("y", v.getCenter().y());
        generator.writeEndObject();

        generator.writeEndObject();
    }
    generator.writeEndArray();

    generator.writeFieldName("Edges");
    generator.writeStartArray();
    for (Entry<Integer, Vertex> vertexEntry : graph.entrySet()) {
        Vertex v = vertexEntry.getValue();
        for (Entry<Integer, Edge>  edgeEntry: v.getNeighbors().entrySet()) {
            generator.writeStartObject();
            Edge e = edgeEntry.getValue();
            String hexLabelColor = encode(e.getLabelColor());
            String hexStrokeColor = encode(e.getStrokeColor());
            generator.writeNumberField("start", e.getStart());
            generator.writeNumberField("end", e.getEnd());
            generator.writeStringField("label", e.getLabel());
            generator.writeStringField("labelColor", hexLabelColor);
            generator.writeStringField("strokeColor", hexStrokeColor);
            generator.writeNumberField("strokeSize", e.getStrokeSize());

            generator.writeFieldName("center");
            generator.writeStartObject();
            generator.writeNumberField("x", e.getLabelCenter().x());
            generator.writeNumberField("y", e.getLabelCenter().y());
            generator.writeEndObject();

            generator.writeEndObject();
        }
    }

    generator.close();
}

```

This code doesn't compile by itself because it depends on some classes that I use in my project, but it gives you the idea. You can find the full source code [here](https://github.com/rendon/graph_illustrator/blob/master/src/edu/inforscience/Main.java).

I hope it helps. Bye!
