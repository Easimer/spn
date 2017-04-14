# spn - 3D raycaster renderer

Supports spheres and light sources.

## Scene file syntax
Each line represent an object in the scene. The first number is the type
of the object. The remaining numbers are the parameters of the object.

| ID  | Name      | Parameters                         |
| --- | --------- | ---------------------------------- |
| 0   | Light     | x, y, z, r, g, b, l                |
| 1   | Sphere    | x, y, z, r                         |
| 2   | Triangle  | x0, y0, z0, x1, y1, z1, x2, y2, z2 |
| 3   | 2.5D Wall | x0, z0, x1, z1                     |

## Lua API
All API methods are in the `spn` table.
These methods are the following:

| Name             | Args   | Description                |
| ---              | ---    | ---                        |
| getlightbyindex  | index  | Returns with light #index  |
| getspherebyindex | index  | Returns with sphere #index |

### Tables
light:

| Field            | Description
| -----            | -----------
| x, y, z          | Position
| r, g, b          | Color
| l                | Luminosity
| setx, sety, setz | Set position
| setr, setg, setb | Set color
| setl             | Set luminosity

sphere:

| Field            | Description
| -----            | -----------
| x, y, z          | Position
| r                | Radius
| setx, sety, setz | Set position
| setr             | Set radius

