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
