/**
 * Compute the coordinates of a n-pointed star.
 *
 * @param n number of points
 * @param center star center
 * @param point first point of the star
 */

void computeStar(int n, Point center, Point point)
{
    double r = center.distance(point),
           theta = 2 * Math.PI / n,
           cx = center.getX(),
           cy = ly((int)center.getY()),
           px = point.getX(),
           py = ly((int)point.getY()),
           beta = Math.atan2(py - cy, px - cx),
           x, y, xPrime, yPrime;

    star.clear();

    for (int i = 0; i < n; i++) {
        x = r * Math.cos(i * theta);
        y = r * Math.sin(i * theta);

        // Rotate the polygon such that the mouse click matches the  star point
        xPrime = x * Math.cos(beta) - y * Math.sin(beta);
        yPrime = x * Math.sin(beta) + y * Math.cos(beta);

        // Translate to it's original position
        xPrime += cx;
        yPrime += cy;
        star.add(new Point((int)Math.round(xPrime), (int)Math.round(yPrime)));

        x = 0.5 * r * Math.cos(i * theta + 0.5 * theta);
        y = 0.5 * r * Math.sin(i * theta + 0.5 * theta);

        xPrime = x * Math.cos(beta) - y * Math.sin(beta);
        yPrime = x * Math.sin(beta) + y * Math.cos(beta);

        xPrime += cx;
        yPrime += cy;
        star.add(new Point((int)Math.round(xPrime), (int)Math.round(yPrime)));
    }
}
