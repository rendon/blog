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
