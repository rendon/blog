<!-- vim: set spelllang=es_MX: -->
---
tags:
    - dev
    - school
    - post
created: 2016-02-23
updated: 2024-05-06
---
# Reporte V: Android web service

Este reporte corresponde al proyecto número 5 de la asignatura Desarrollo de Aplicaciones para Tecnologías Móviles.

## Definición del problema

<blockquote>Desarrollar un Web service (en el lenguaje que más les agrade) capaz de manipular una base de datos a petición del cliente, en este caso, el cliente será una aplicación móvil para la plataforma Android.</blockquote>

## Definiciones

Como este reporte forma parte de una serie de reportes, vamos a omitir la teoría sobre Web services puesto que ya se abordo en el reporte número [II](/?p=865).

## Propuesta de solución

Nuevamente, el problema nos da la flexibilidad de elegir que problema modelar, la propuesta es la siguiente:

<blockquote>Desarrollar una aplicación móvil para el control requisiciones, similar a los dispositivos que utilizan los agentes de venta cuando salen a levantar pedidos.</blockquote>

### El cliente

La aplicación móvil deberá cumplir con los siguientes requisitos:

<ul>
  <li>La aplicación permitirá consultar la lista de clientes.</li>
  <li>La aplicación permitirá consultar la lista de productos.</li>
  <li>La aplicación permitirá registrar pedidos.</li>
  <li>La aplicación permitirá consultar la lista de pedidos.</li>
  <li>La aplicación deberá tener la capacidad de trabajar tanto _online_ como _offline_.</li>
  <li>La aplicación permitirá subir los registros al servidor.</li>
  <li>La aplicación permitirá contactar al servidor para actualizar catálogos.</li>
</ul>

### El servidor

Un Web service desarrollado en PHP que manipula una base de datos MySQL. A continuación la lista de servicios que vamos desarrollar:

<ul>
  <li>**PutRegisters(requests[], details[])** Recibe los datos de la aplicación móvil y los agrega a la base de datos, en caso de que aun no existan.</li>
  <li>**GetAllClients()** Retorna al cliente la lista de clientes. Este servicio forma parte de la actualización de catálogos.</li>
  <li>**GetAllProducts()** Retorna al cliente la lista de productos. Este servicio forma parte de la actualización de catálogos.</li>
</ul>

### Requisitos

Para poder realizar esta práctica se necesita lo siguiente:

<ul>
  <li>Debian GNU/Linux Wheezy</li>
  <li>Un servidor LAMP (Linux + Apache + MySQL + PHP). Véase el reporte [II](/?p=865).</li>
  <li>El SDK de Android instalado y configurado. Véase el reporte [I](/?p=833).</li>
  <li>Un dispositivo móvil con Android 2.3 o el emulador de Android.</li>
  <li>IntelliJ IDEA 12.</li>
</ul>

## Desarrollo del Servidor

El Web service para esta aplicación es exactamente el mismo que se empleamos en el proyecto anterior (cliente Blackberry). A continuación se muestra el modelo de la base de datos para refrescar la memoria.

![Modelo de datos](/report-v-android-web-service/bbws_data_model.png)

Lo relevante de la implementación del Web service lo pueden encontrar en los reportes [III](/report-iii-wp8-web-services/) y [IV](/report-iv-bb10-web-service/), colocar nuevamente el código aquí sería redundante y ocuparía mucho espacio.

## La base de datos local

Uno de los requisitos de nuestra aplicación es que debe de funcionar de forma desconectada, por ende, es necesario crear una replica del modelo de datos en nuestra aplicación móvil. A continuación se muestra como se manipulan los datos en de formal local, el SGBD es SQLite.

Lo primero es crear las clases necesarias que representaran a nuestras tablas.

```
package com.inforscience.requisition.model;

public class Client {
    private int idClient;
    private String name;
    private String middleName;
    private String lastName;
    private String address;

    public Client() { };

    public Client(int idClient, String name, String middleName,
                  String lastName, String address)
    {
        this.idClient = idClient;
        this.name = name;
        this.middleName = middleName;
        this.lastName = lastName;
        this.address = address;
    }

    public int getIdClient()
    {
        return idClient;
    }

    public void setIdClient(int idClient)
    {
        this.idClient = idClient;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public String getMiddleName()
    {
        return middleName;
    }

    public void setMiddleName(String middleName)
    {
        this.middleName = middleName;
    }

    public String getLastName()
    {
        return lastName;
    }

    public void setLastName(String lastName)
    {
        this.lastName = lastName;
    }

    public String getAddress()
    {
        return address;
    }

    public void setAddress(String address)
    {
        this.address = address;
    }

    @Override
    public String toString()
    {
        return getName() + " " + getMiddleName() + " " + getLastName();
    }
}
```

```
package com.inforscience.requisition.model;

public class Product {
    private int idProduct;
    private String description;

    public Product() { }

    public Product(int idProduct, String description)
    {
        this.idProduct = idProduct;
        this.description = description;
    }

    public int getIdProduct()
    {
        return idProduct;
    }

    public void setIdProduct(int idProduct)
    {
        this.idProduct = idProduct;
    }

    public String getDescription()
    {
        return description;
    }

    public void setDescription(String description)
    {
        this.description = description;
    }

    @Override
    public String toString()
    {
        return getDescription();
    }
}
```

```
package com.inforscience.requisition.model;

public class Request {
    private int idRequest;
    private int idClient;
    private String requestDate;

    public Request() { }

    public Request(int idRequest, int idClient, String requestDate)
    {
        this.idRequest = idRequest;
        this.idClient = idClient;
        this.requestDate = requestDate;
    }

    public int getIdRequest()
    {
        return idRequest;
    }

    public void setIdRequest(int idRequest)
    {
        this.idRequest = idRequest;
    }

    public int getIdClient()
    {
        return idClient;
    }

    public void setIdClient(int idClient)
    {
        this.idClient = idClient;
    }

    public String getRequestDate()
    {
        return requestDate;
    }

    public void setRequestDate(String requestDate)
    {
        this.requestDate = requestDate;
    }
}
```

```
package com.inforscience.requisition.model;

public class Detail {
    private int idDetail;
    private int idRequest;
    private int idProduct;
    private int amount;
    private String description; // An ugly work around

    public Detail()
    {
        setIdDetail(0);
        setIdRequest(0);
        setIdProduct(0);
        setAmount(0);
        setDescription("");
    }

    public Detail(int idDetail, int idRequest, int idProduct, int amount)
    {
        this.idDetail = idDetail;
        this.idRequest = idRequest;
        this.idProduct = idProduct;
        this.amount = amount;
    }

    public int getIdDetail()
    {
        return idDetail;
    }

    public void setIdDetail(int idDetail)
    {
        this.idDetail = idDetail;
    }

    public int getIdRequest()
    {
        return idRequest;
    }

    public void setIdRequest(int idRequest)
    {
        this.idRequest = idRequest;
    }

    public int getIdProduct()
    {
        return idProduct;
    }

    public void setIdProduct(int idProduct)
    {
        this.idProduct = idProduct;
    }

    public int getAmount()
    {
        return amount;
    }

    public void setAmount(int amount)
    {
        this.amount = amount;
    }

    public String getDescription()
    {
        return description;
    }

    public void setDescription(String description)
    {
        this.description = description;
    }

    @Override
    public String toString()
    {
        return getAmount() + " |  " + getDescription();
    }
}
```

Para simplificarnos las cosas vamos a crear un clase auxiliar (un _Helper_) para que realice todas las tareas que tienen que ver con la base de datos, como son la creación de las tablas (en caso de que no existan), inserción de registros y consulta de los mismos:

```
package com.inforscience.requisition.model;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;

public class DBManager {
    public static final String DB_NAME = "pedidos";

    private static final String DB_CREATE_CLIENT =
              "CREATE TABLE IF NOT EXISTS Client (IdClient INTEGER PRIMARY KEY,"
            + "Name VARCHAR(20), MiddleName VARCHAR(20), LastName VARCHAR(20), "
            + "Address VARCHAR(100))";

    private static final String UNIQUE_FULL_NAME_CONSTRAINT =
              "CREATE UNIQUE INDEX IF NOT EXISTS unique_fullname ON "
            + "Client(Name, MiddleName, LastName, Address)";

    private static final String DB_CREATE_REQUEST =
              "CREATE TABLE IF NOT EXISTS Request(IdRequest INTEGER PRIMARY KEY"
            + " AUTOINCREMENT, IdClient INTEGER, RequestDate DATETIME, "
            + " FOREIGN KEY (IdClient) REFERENCES Client (IdClient))";

    private static final String UNIQUE_REQUEST_CONSTRAINT =
              "CREATE UNIQUE INDEX IF NOT EXISTS unique_request "
            + "ON Request(IdRequest, IdClient)";

    private static final String DB_CREATE_PRODUCT =
              "CREATE TABLE IF NOT EXISTS Product(IdProduct "
            + "INTEGER PRIMARY KEY, Description VARCHAR(100))";

    private static final String DB_CREATE_DETAIL =
             "CREATE TABLE IF NOT EXISTS Detail(IdDetail INTEGER PRIMARY "
            + "KEY AUTOINCREMENT, IdRequest INTEGER, IdProduct INTEGER, "
            + "Amount INTEGER, FOREIGN KEY (IdRequest) REFERENCES Request "
            + "(IdRequest), FOREIGN KEY(IdProduct) "
            + "REFERENCES Product(IdProduct))";

    private static final String UNIQUE_DETAIL_CONSTRAINT =
              "CREATE UNIQUE INDEX IF NOT EXISTS unique_detail "
            + "ON Detail(IdDetail, IdRequest)";

    private DBManager() { }

    public static void initialize(SQLiteDatabase db)
    {
        db.execSQL(DB_CREATE_CLIENT);
        db.execSQL(DB_CREATE_PRODUCT);
        db.execSQL(DB_CREATE_REQUEST);
        db.execSQL(DB_CREATE_DETAIL);
    }

    public static long insertClient(Client client, SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put("IdClient", client.getIdClient());
        values.put("Name", client.getName());
        values.put("MiddleName", client.getMiddleName());
        values.put("LastName", client.getLastName());
        values.put("Address", client.getAddress());

        return db.insert("Client", null, values);
    }


    public static long insertProduct(Product product, SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put("IdProduct", product.getIdProduct());
        values.put("Description", product.getDescription());

        return db.insert("Product", null, values);
    }


    public static long insertRequest(Request request, SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put("IdClient", request.getIdClient());
        values.put("RequestDate", request.getRequestDate());

        return db.insert("Request", null, values);
    }

    public static long insertDetail(Detail detail, SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put("IdRequest", detail.getIdRequest());
        values.put("IdProduct", detail.getIdProduct());
        values.put("Amount", detail.getAmount());

        return db.insert("Detail", null, values);
    }

    public static ArrayList<Client> selectClients(SQLiteDatabase db)
    {
        String[] fields = new String[] {"IdClient", "Name", "MiddleName",
                "LastName", "Address"};

        Cursor r = db.query("Client", fields, null, null, null, null, null);

        ArrayList<Client> clients = new ArrayList<Client>();
        if (r.moveToFirst()) {
            do {
                Client c = new Client();
                c.setIdClient(Integer.parseInt(r.getString(0)));
                c.setName(r.getString(1));
                c.setMiddleName(r.getString(2));
                c.setLastName(r.getString(3));
                c.setAddress(r.getString(4));
                clients.add(c);
            } while (r.moveToNext());
        }

        return clients;
    }

    public static ArrayList<Request> selectRequests(SQLiteDatabase db)
    {
        String[] fields = new String[] {"IdRequest", "IdClient", "RequestDate"};
        Cursor r = db.query("Request", fields, null, null, null, null, null);

        ArrayList<Request> requests = new ArrayList<Request>();
        if (r.moveToFirst()) {
            do {
                Request request = new Request();
                request.setIdRequest(Integer.parseInt(r.getString(0)));
                request.setIdClient(Integer.parseInt(r.getString(1)));
                request.setRequestDate(r.getString(2));
                requests.add(request);
            } while (r.moveToNext());
        }

        return requests;
    }

    public static ArrayList<Product> selectProducts(SQLiteDatabase db)
    {
        String[] fields = new String[] {"IdProduct", "Description"};
        Cursor r = db.query("Product", fields, null, null, null, null, null);

        ArrayList<Product> products = new ArrayList<Product>();
        if (r.moveToFirst()) {
            do {
                Product p = new Product();
                p.setIdProduct(Integer.parseInt(r.getString(0)));
                p.setDescription(r.getString(1));
                products.add(p);
            } while (r.moveToNext());
        }

        return products;
    }

    public static ArrayList<Detail> selectDetails(SQLiteDatabase db)
    {
        String[] fields = new String[] {"IdDetail", "IdRequest",
                "IdProduct", "Amount"};
        Cursor r = db.query("Detail", fields, null, null, null, null, null);

        ArrayList<Detail> details = new ArrayList<Detail>();
        if (r.moveToFirst()) {
            do {
                Detail d = new Detail();
                d.setIdDetail(Integer.parseInt(r.getString(0)));
                d.setIdRequest(Integer.parseInt(r.getString(1)));
                d.setIdProduct(Integer.parseInt(r.getString(2)));
                d.setAmount(Integer.parseInt(r.getString(3)));
                details.add(d);
            } while (r.moveToNext());
        }

        return details;
    }

    public static void clean(SQLiteDatabase db)
    {
        db.delete("Detail", null, null);
        db.delete("Request", null, null);
        db.delete("Product", null, null);
        db.delete("Client", null, null);
    }


    public static ArrayList<String> queryRequests(SQLiteDatabase db)
    {
        Cursor r = db.rawQuery(
                  "SELECT Request.IdRequest, Client.Name, Client.MiddleName, "
                + "Client.LastName, Request.RequestDate, Detail.Amount, "
                + "Product.Description FROM Request, Client, Detail, Product "
                + "WHERE Detail.IdRequest = Request.IdRequest AND "
                + "Request.IdClient = Client.IdClient AND "
                + "Detail.IdProduct = Product.IdProduct", null);

        TreeMap<String, ArrayList<String>> map =
                new TreeMap<String, ArrayList<String>>();
        ArrayList<String> requests = new ArrayList<String>();

        if (r.moveToFirst()) {
            do {
                String key  = r.getString(0) + ": "
                            + r.getString(1) + " "
                            + r.getString(2) + " "
                            + r.getString(3) + "\n";
                String date = r.getString(4).toString();

                for (int i = 0; i < key.length(); i++) {
                    if (Character.isLetter(key.charAt(i)))
                        break;
                    date = " " + date;
                }

                key += date;

                String amount = r.getString(5);
                while (amount.length() < 4)
                    amount = " " + amount;

                String value = amount + " | " + r.getString(6);

                if (map.containsKey(key)) {
                    ArrayList<String> a = map.get(key);
                    a.add(value);
                } else {
                    ArrayList<String> a = new ArrayList<String>();
                    a.add(value);
                    map.put(key, a);
                }
            } while (r.moveToNext());
        }

        for (Map.Entry<String, ArrayList<String>> entry : map.entrySet()) {
            requests.add(entry.getKey());
            for (int i = 0; i < entry.getValue().size(); i++) {
                requests.add(entry.getValue().get(i));
            }
        }

        return requests;
    }
}
```

Podrán observar que cada uno de los métodos recibe un objecto de tipo _SQLiteDatabase_, este objecto lo creamos en la actividad principal (_MainActivity.java_) de nuestra aplicación y se proporciona al a las actividades restantes. He aquí la parte relevante:

```
/* Método onCreate() */

database = openOrCreateDatabase(DBManager.DB_NAME,
            Context.MODE_PRIVATE, null);
DBManager.initialize(database);

tabHost.setCurrentTab(2);
SearchActivity searchActivity = (SearchActivity)getLocalActivityManager()
        .getCurrentActivity();
searchActivity.setDatabase(database);

tabHost.setCurrentTab(1);
ShopActivity shopActivity = (ShopActivity)getLocalActivityManager()
                                .getCurrentActivity();
shopActivity.setDatabase(database);
shopActivity.populateCatalogs();


tabHost.setCurrentTab(0);
HomeActivity homeActivity = (HomeActivity)getLocalActivityManager()
                                .getCurrentActivity();
homeActivity.setDatabase(database);
homeActivity.setShopActivity(shopActivity);
```

Como su nombre lo indica, el método _openOrCreateDatabase()_ abre nuestra base de datos o la crea en caso de que aun no exista.

## Comunicación con el Web service

Al igual que con Qt, trabajar con Web services en Java es un poco tedioso ya que no hay soporte nativo (¿Lo hay?) para trabajar con ellos. Existen algunas bibliotecas para trabajar con Web services pero son demasiado complejas y lo que necesitamos para esta aplicación es algo sencillo, por ello vamos a crear nuestro propio proxy.

```
package com.inforscience.requisition.net;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import android.util.Log;

import com.inforscience.requisition.model.Client;
import com.inforscience.requisition.model.Detail;
import com.inforscience.requisition.model.Product;
import com.inforscience.requisition.model.Request;

public class WebService {
    public static final String WS_URL =
        "http://192.168.1.200/request_ws/index.php";
    public static final String MSG_GET_ALL_CLIENTS =
          "<?xml version='1.0'?> <soapenv:Envelope xmlns:soapenv="
        + "'http://schemas.xmlsoap.org/soap/envelope/' xmlns:req='Request'> "
        + "<soapenv:Header/> <soapenv:Body> <req:GetAllClients/> "
        + "</soapenv:Body> </soapenv:Envelope>";

    public static final String MSG_GET_ALL_PRODUCTS =
          "<soapenv:Envelope xmlns:soapenv='http://schemas.xmlsoap.org/soap/"
        + "envelope/' xmlns:req='Request'> <soapenv:Header/> <soapenv:Body> "
        + "<req:GetAllProducts/> </soapenv:Body> </soapenv:Envelope>";


    private WebService() { }

    public static ArrayList<Client> queryClients() throws Exception
    {
        URL url = new URL(WS_URL);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();

        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type:", "text/xml");

        conn.setDoOutput(true);
        DataOutputStream out = new DataOutputStream(conn.getOutputStream());
        out.writeBytes(MSG_GET_ALL_CLIENTS);
        out.flush();
        out.close();

        return XMLParser.parseClients(conn.getInputStream());
    }

    public static ArrayList<Product> queryProducts() throws Exception
    {
        URL url = new URL(WS_URL);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type:", "text/xml");
        conn.setDoOutput(true);
        DataOutputStream out = new DataOutputStream(conn.getOutputStream());
        out.writeBytes(MSG_GET_ALL_PRODUCTS);
        out.flush();
        out.close();

        return XMLParser.parseProducts(conn.getInputStream());
    }

    public static void putRegisters(ArrayList<Request> R,
                             ArrayList<Detail> D) throws Exception
    {
        String header =
                  "<soapenv:Envelope "
                + "xmlns:soapenv='http://schemas.xmlsoap.org/soap/envelope/'"
                + " xmlns:req='Request'> <soapenv:Header/> <soapenv:Body> "
                + " <req:PutRegisters>";

        String footer   = "</req:PutRegisters> "
                        + "</soapenv:Body> "
                        + "</soapenv:Envelope>";

        String requests = "\n<RequestItems>\n";

        int n = R.size();
        for (int i = 0; i < n; i++) {
            Request r = R.get(i);
            requests += "<item>";
            requests += "<IdRequest>" + r.getIdRequest() + "</IdRequest>";
            requests += "<IdClient>" + r.getIdClient()+ "</IdClient>";
            requests += "<RequestDate>" + r.getRequestDate() + "</RequestDate>";

            requests += "</item>" + "\n";
        }
        requests += "</RequestItems>";

        String details = "<DetailItems>" + "\n";
        n = D.size();
        for (int i = 0; i < n; i++) {
            Detail d = D.get(i);
            details += "<item>";
            details += "<IdDetail>" + d.getIdDetail() + "</IdDetail>";
            details += "<IdRequest>" + d.getIdRequest() + "</IdRequest>";
            details += "<IdProduct>" + d.getIdProduct() + "</IdProduct>";
            details += "<Amount>" + d.getAmount() + "</Amount>";
            details += "</item>\n";
        }

        details += "</DetailItems>";

        String message = header + requests + "\n" + details + "\n" + footer;
        URL url = new URL(WS_URL);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type:", "text/xml");

        conn.setDoOutput(true);
        DataOutputStream out = new DataOutputStream(conn.getOutputStream());
        out.writeBytes(message);
        out.flush();
        out.close();

        InputStreamReader is = new InputStreamReader(conn.getInputStream());
        BufferedReader reader = new BufferedReader(is);
        String line, response = "";
        while ((line = reader.readLine()) != null)
            response += line;

        Log.w("RESPONSE", response);
    }
}
```

Este código es ni más ni menos que el que ocupamos con Blackberry, pero en Java.

## El cliente

En este apartado vamos a ver como construir la aplicación en Android y cómo se realizan las operaciones.

En Android, al igual que con otras plataformas, es posible construir la interfaz directamente desde código usando Java, sin embargo, lo recomendable es separar la interfaz de la lógica de la aplicación ya que esto nos facilitará el mantenimiento de nuestro software. Una interfaz gráfica para Android se puede describir utilizando el lenguaje XML.

En esta ocasión he optado por utilizar el diseñador de interfaces que viene con IntelliJ IDEA, sin embargo, al final el resultado es el mismo, código XML.

### Creación del proyecto

Para evitar ambigüedades vamos a ilustrar paso a paso cómo crear el proyecto en IntelliJ IDEA.

![Página de inicio de IntelliJ IDEA](/report-v-android-web-service/androidws_cp_1.png)
![Nombre del proyecto](/report-v-android-web-service/androidws_cp_2.png)
![Nombre del paquete y configuración de dispositivo](/report-v-android-web-service/androidws_cp_3.png)
![Estamos listos para empezar](/report-v-android-web-service/androidws_cp_4.png)

### La página principal

La siguiente figura muestra como lucirá la página principal de nuestra aplicación:

![Página principal](/report-v-android-web-service/androidws_home.png)

El diseño correspondiente en XML es el siguiente:

```
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:orientation="vertical"
              android:layout_width="match_parent"
              android:layout_height="match_parent">


    <LinearLayout
            android:orientation="horizontal"
            android:layout_width="fill_parent"
            android:layout_height="wrap_content"
            android:layout_gravity="center">
        <ImageView
                android:layout_width="70dp"
                android:layout_height="70dp"
                android:id="@+id/imageView"
                android:background="@drawable/ic_itch"/>
        <TextView
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:text="Desarrollo de Aplicaciones kara Tecnologías Móviles"
                android:id="@+id/textView" android:layout_gravity="center"
                android:paddingLeft="10dp" android:textSize="16dp"/>
    </LinearLayout>
    <LinearLayout
            android:orientation="vertical"
            android:layout_width="fill_parent"
            android:layout_height="fill_parent" android:layout_gravity="center"
            android:gravity="center_vertical">
        <ListView
                android:layout_width="fill_parent"
                android:layout_height="wrap_content"
                android:id="@+id/listView"/>
        <Button
                android:layout_width="fill_parent"
                android:layout_height="wrap_content"
                android:text="Enviar registros al servidor"
                android:id="@+id/put_registers_button"
                android:layout_gravity="center"/>
        <Button
                android:layout_width="fill_parent"
                android:layout_height="wrap_content"
                android:text="Limpiar registros y actualizar catalogos"
                android:id="@+id/update_catalogs_button"/>
    </LinearLayout>
</LinearLayout>
```

El siguiente listado muestra como se programa el comportamiento de los dos botones:

```
@Override
public void onCreate(Bundle savedInstanceState)
{
    super.onCreate(savedInstanceState);
    setContentView(R.layout.home);

    Button updateButton = (Button)findViewById(R.id.update_catalogs_button);
    updateButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View view)
        {
            Toast.makeText(getApplicationContext(), "!Espere, por favor!",
                           Toast.LENGTH_SHORT).show();
            DBManager.clean(database);
            Spinner clientSpinner = (Spinner)shopActivity
                                        .findViewById(R.id.client_list);
            try {
                ArrayList<Client> clients = WebService.queryClients();
                ArrayAdapter<Client> adapter =
                        new ArrayAdapter<Client>(getApplicationContext(),
                                android.R.layout.select_dialog_item,
                                clients);

                clientSpinner.setAdapter(adapter);
                clientSpinner.setBackgroundColor(Color.GRAY);

                int n = clients.size();
                for (int i = 0; i < n; i++)
                    DBManager.insertClient(clients.get(i), database);

            } catch (Exception e) {
                Log.e("EXCEPTION", e.toString());
            }


            Spinner productSpinner = (Spinner)shopActivity
                                        .findViewById(R.id.product_list);
            try {
                ArrayList<Product> products = WebService.queryProducts();
                ArrayAdapter<Product> adapter =
                        new ArrayAdapter<Product>(getApplicationContext(),
                                android.R.layout.select_dialog_item,
                                products);

                int n = products.size();
                for (int i = 0; i < n; i++)
                    DBManager.insertProduct(products.get(i), database);

                productSpinner.setAdapter(adapter);
                productSpinner.setBackgroundColor(Color.GRAY);
            } catch (Exception e) {
                Log.e("EXCEPTION", e.toString());
            }

            Toast.makeText(getApplicationContext(), "!Listo!", Toast.LENGTH_SHORT).show();
        }
    });

    Button putButton = (Button)findViewById(R.id.put_registers_button);
    putButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View view)
        {
            ArrayList<Request> R = DBManager.selectRequests(database);
            ArrayList<Detail> D = DBManager.selectDetails(database);
            try {
                Toast.makeText(getApplicationContext(),
                               "!Espere, por favor!",
                               Toast.LENGTH_SHORT).show();
                WebService.putRegisters(R, D);
                Toast.makeText(getApplicationContext(), "!Listo!",
                               Toast.LENGTH_SHORT).show();
            } catch (Exception e) {
                Log.e("EXCEPTION", e.toString());
            }
        }
    });

}
```


### Registro de pedidos

A continuación se ilustra la interfaz para registrar pedidos.

![Registro de pedidos](/report-v-android-web-service/androidws_shop.png)

La interfaz esta descrita de la siguiente manera:

```
<?xml version="1.0" encoding="utf-8"?>
<linearlayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:orientation="vertical"
              android:layout_width="match_parent"
              android:layout_height="match_parent">
    <linearlayout
            android:orientation="vertical"
            android:layout_width="fill_parent"
            android:layout_height="280dp" android:layout_gravity="center"
            android:gravity="top">
        <linearlayout
                android:orientation="horizontal"
                android:layout_width="fill_parent"
                android:layout_height="50dp"
                android:layout_gravity="center">
            <spinner
                    android:layout_width="200dp"
                    android:layout_height="fill_parent"
                    android:id="@+id/product_list"
                    android:layout_gravity="center"/>
            <edittext
                    android:layout_width="60dp"
                    android:layout_height="fill_parent"
                    android:id="@+id/amount_text"
                    android:layout_gravity="center"
                    android:inputtype="phone"
                    />
            <button
                    android:layout_width="fill_parent"
                    android:layout_height="fill_parent"
                    android:id="@+id/add_item_button"
                    android:text="+"/>
        </linearlayout>
        <listview
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:id="@+id/new_items_list"
                android:layout_gravity="center"/>
    </linearlayout>

    <linearlayout
            android:orientation="vertical"
            android:layout_width="fill_parent"
            android:layout_height="fill_parent" android:layout_gravity="center"
            android:gravity="bottom">


        <spinner
                android:layout_width="fill_parent"
                android:layout_height="wrap_content"
                android:id="@+id/client_list"
                android:layout_gravity="center"/>
        <button
                android:layout_width="fill_parent"
                android:layout_height="wrap_content"
                android:text="guardar pedido"
                android:id="@+id/save_request_button"
                android:layout_gravity="center"/>
    </linearlayout>
</linearlayout>
```

La lógica detrás del botón que agrega artículos a la lista ("+") es la siguiente:

```
Button addItemButton = (Button)findViewById(R.id.add_item_button);
addItemButton.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View view)
    {
        EditText editText = (EditText)findViewById(R.id.amount_text);

        int amount = 0;
        try {
            amount = Integer.parseInt(editText.getText().toString());
        } catch (NumberFormatException e) {
            Toast.makeText(getApplicationContext(),
                    "La cantidad no es válida.",
                    Toast.LENGTH_LONG).show();
            return;
        }

        Spinner products = (Spinner)findViewById(R.id.product_list);
        Product p = (Product)products.getSelectedItem();

        Detail detail = new Detail();
        detail.setIdProduct(p.getIdProduct());
        detail.setAmount(amount);
        detail.setDescription(p.getDescription());
        detailList.add(detail);
        detailArrayAdapter.notifyDataSetChanged();

        editText.setText("");
    }
    });
```

Ahora para el botón que almacena el pedido en la base de datos:

```
Button saveRequestButton;
saveRequestButton = (Button)findViewById(R.id.save_request_button);
saveRequestButton.setOnClickListener(new View.OnClickListener() {
    @Override
    public void onClick(View view)
    {
        if (detailList.isEmpty()) {
            Toast.makeText(getApplicationContext(),
                    "No hay artículos que guardar.",
                    Toast.LENGTH_SHORT).show();
            return;
        }

        Spinner clientSpinner = (Spinner)findViewById(R.id.client_list);
        Client client = (Client)clientSpinner.getSelectedItem();
        int idClient = client.getIdClient();
        Request request = new Request();
        request.setIdClient(idClient);
        request.setRequestDate(rightNow());
        long idRequest = DBManager.insertRequest(request, database);

        boolean ok = true;

        if (idRequest == -1) {
            Toast.makeText(getApplicationContext(),
                    "Ocurrio error al intentar guardar el pedido.",
                    Toast.LENGTH_LONG).show();
            return;
        }

        int n = detailList.size();
        for (int i = 0; i < n; i++) {
            Detail detail = detailList.get(i);
            detail.setIdRequest((int)idRequest);
            long id = DBManager.insertDetail(detail, database);
            if (id == -1) {
                Toast.makeText(getApplicationContext(),
                        "ERROR AL INSERTAR DETALLE",
                        Toast.LENGTH_LONG).show();
                ok = false;
            }
        }

        if (ok) {
            detailList.clear();
            detailArrayAdapter.notifyDataSetChanged();

            Toast.makeText(getApplicationContext(),
                    "El pedido se guardo satisfactoriamente.",
                    Toast.LENGTH_SHORT).show();
        }

    }
});
```


### Consulta de pedidos

Nuestra aplicación también permite visualizar la lista de pedidos que tenemos en nuestra base de datos local.

![Consulta de pedidos](/report-v-android-web-service/androidws_query.png)

El código XML que describe a esta interfaz es el siguiente:

```
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:orientation="vertical"
              android:layout_width="fill_parent"
              android:layout_height="fill_parent">

    <LinearLayout
            android:orientation="horizontal"
            android:layout_width="fill_parent"
            android:layout_height="40dp"
            android:gravity="center_vertical">
        <TextView
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:text="Lista de pedidos:"
                android:id="@+id/textView"
                android:layout_gravity="left|center_vertical"
                android:layout_weight="1"/>
        <Button
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:text="Actualizar"
                android:id="@+id/refresh_query_button"
                android:layout_gravity="center"
                android:layout_weight="1"/>
    </LinearLayout>
    <ListView
            android:layout_width="fill_parent"
            android:layout_height="fill_parent"
            android:id="@+id/request_list"/>
</LinearLayout>
```

Y la lógica detrás del botón "Actualizar" es:

```
@Override
public void onCreate(Bundle savedInstanceBundle)
{
    super.onCreate(savedInstanceBundle);
    setContentView(R.layout.search);

    ListView listView = (ListView)findViewById(R.id.request_list);
    requests = new ArrayList<String>();
    requestAdapter = new RequestAdapter(this, requests);
    listView.setAdapter(requestAdapter);
    Button refreshButton = (Button)findViewById(R.id.refresh_query_button);
    refreshButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View view)
        {
            ArrayList<String> items = DBManager.queryRequests(database);
            requests.clear();
            for (int i = 0; i < items.size(); i++)
                requests.add(items.get(i));

            requestAdapter.notifyDataSetChanged();
        }
    });
}
```

Hasta aquí las explicaciones, al final se proporciona el código completo de la aplicación.


## Código fuente

El código del servidor y del cliente están disponibles en Bitbucket en las siguientes direcciones:

[https://bitbucket.org/rendon/request_ws](https://bitbucket.org/rendon/request_ws)
[https://bitbucket.org/rendon/requisition_android](https://bitbucket.org/rendon/requisition_android)

O bien pueden clonar los proyectos:

```
$ git clone https://rendon@bitbucket.org/rendon/request_ws.git
$ git clone https://rendon@bitbucket.org/rendon/requisitionandroid.git
```

La licencia del Web service y de la aplicación cliente es GPLv3.

## Por hacer

Mejorar la interfaz gráfica. La personalización de los elementos gráficos es un poco tediosa, al menos en la version 2.3, espero que esto halla mejorado en las versiones más recientes.


## Referencias
- [Documentación de Android](https://developer.android.com/index.html)
