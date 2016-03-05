/**
 * Compute the coordinates of a polygon.
 *
 * @param n number of sides
 * @param center center of the polygon
 * @param point point of the first corner
 */
void computePolygon(int n, Point center, Point point)
{
    double r = center.distance(point),
           cx = center.getX(),
           cy = ly((int)center.getY()),
           px = point.getX(),
           py = ly((int)point.getY()),
           theta = 2 * Math.PI / n,
           beta = Math.atan2(py - cy, px - cx),
           x, y, xPrime, yPrime;

    polygon.clear();

    for (int i = 0; i < n; i++) {
        x = r * Math.cos(i * theta);
        y = r * Math.sin(i * theta);

        // Rotate the polygon such that the mouse click matches the  polygon corner
        xPrime = x * Math.cos(beta) - y * Math.sin(beta);
        yPrime = x * Math.sin(beta) + y * Math.cos(beta);

        // Translate the polygon to it's original position
        xPrime += cx;
        yPrime += cy;

        polygon.add(new Point((int)Math.round(xPrime), (int)Math.round(yPrime)));
    }
}
