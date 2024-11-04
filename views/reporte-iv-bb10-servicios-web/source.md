<!-- vim: set spelllang=es_MX: -->

---
tags:
    - dev
    - web-services
    - post
created: 2016-02-18
updated: 2024-05-07
---
# Reporte IV BlackBerry 10 Web service

Este reporte corresponde al proyecto número 4 de la asignatura Desarrollo de Aplicaciones para Tecnologías Móviles.

<div style="padding: 10px; border: 1px solid red;">
  **NOTA**
  El Web service que vamos a utilizar no es el mismo que el del proyecto anterior (cliente Windows Phone), se han hecho algunas modificaciones al modelo de datos y por lo tanto al Web service, para cumplir con las observaciones hechas por el profesor:

  <ul>
    <li>El cliente no debe de modificar los catálogos (clientes y productos), únicamente agregar registros.</li>
    <li>La aplicación cliente no debe tener una réplica completa de la base de datos, únicamente los datos de los registros que se han realizado con la misma.</li>
  </ul>
</div>

## Definición del problema

<blockquote>Desarrollar un Web service (en el lenguaje que más les agrade) capaz de manipular una base de datos a petición del cliente, en este caso, el cliente será una aplicación móvil para la plataforma Blackberry 10.</blockquote>

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

## Requisitos

Para poder realizar esta práctica se necesita lo siguiente:

<ul>
  <li>Debian GNU/Linux Wheezy</li>
  <li>Un servidor LAMP (Linux + Apache + MySQL + PHP), ya vimos como configurar uno del reporte número 2.</li>
  <li>Momentics IDE 2.0, fue mi primera opción pero después cambie a Qt Creator, solo lo incluyo porque al instalar éste IDE se descargan todas las bibliotecas necesarias.</li>
  <li>Qt 5 y Qt Creator, versiones beta ([http://qt-project.org/downloads](http://qt-project.org/downloads)), solo descarga e instala con el clásico "Next, Next, Next...".</li>
  <li>El simulador de Blackberry ([developer.blackberry.com/devzone/develop/simulator/simulator_installing.html](https://developer.blackberry.com/devzone/develop/simulator/simulator_installing.html)).</li>
</ul>

### Instalación del simulador

El simulador es una imagen de disco que podemos usar con VMware Player ([www.vmware.com](https://www.vmware.com)), simplemente instala VMware Player y carga la imagen del simulador.

El simulador consume muchos recursos, por defecto el simulador buscará una tarjeta de gráficos en nuestro sistema, si no contamos con una nos encontraremos con esto:

![El emulador no arranca](/report-iv-bb10-web-service/bbws_start_service_screen.png)

La solución es entrar en uno de los modos seguros, en mi caso he optado por la resolución de pantalla 720x720 y modo seguro (opción 5).

![Elige el modo seguro si no se cuenta con una tarjeta gráfica](/report-iv-bb10-web-service/bbws_start_service_screen_sol.png)


### Configuración de Qt Creator

Qt Creator ya viene con soporte para BlackBerry, sin embargo habrá que configurar algunas cosas. Vamos a asumir que Momentics IDE fue instalado en el directorio _/opt/bbndk_ y Qt fue instalado en _/opt/qt5_.

Vamos a ejecutar Qt Creator desde la consola, pero antes vamos a ejecutar un script de configuración que viene incluido con Momentics IDE.

```
/opt/bbndk/bbndk-env_10_2_0_1155.sh
/opt/qt5/Tools/QtCreator/bin/qtcreator
```

El script de configuración exporta algunas variables de entorno que Qt Creator necesita para ubicar las herramientas necesarias. Una vez abierto Qt Creator, vamos a agregar el compilador: Tools -> Options ->  Build & Run.

![Configuración del compilador para BlackBerry](/report-iv-bb10-web-service/bbws_qtcreator_qcc.png)

Ahora hay que configurar el simulador: Tool -> Options -> Devices -> Add...:

![Agrega un nuevo dispositivo tipo BlackBerry](/report-iv-bb10-web-service/bbws_qtcreator_add_sim_1.png)

Especificamos la IP del simulador:

![Detección del simulador](/report-iv-bb10-web-service/bbws_qtcreator_add_sim_2.png)

![Detección del simulador](/report-iv-bb10-web-service/bbws_qtcreator_add_sim_3.png)

![Detección del simulador](/report-iv-bb10-web-service/bbws_qtcreator_add_sim_4.png)

La IP la podemos encontrar en la parte inferior derecha del simulador:

![IP del simulador](/report-iv-bb10-web-service/bbws_simulator_ip.png)

Ahora deberíamos poder probar una aplicación "¡Hola, mundo!":

![Nuevo proyecto, Paso 1](/report-iv-bb10-web-service/bbws_hello_world_1.png)
![Nuevo proyecto, Paso 2](/report-iv-bb10-web-service/bbws_hello_world_2.png)
![Nuevo proyecto, Paso 3](/report-iv-bb10-web-service/bbws_hello_world_3.png)
![Nuevo proyecto, Paso 4](/report-iv-bb10-web-service/bbws_hello_world_4.png)
![Nuevo proyecto, Paso 5](/report-iv-bb10-web-service/bbws_hello_world_5.png)
![Nuevo proyecto, Paso 6](/report-iv-bb10-web-service/bbws_hello_world_6.png)

Para más información sobre la configuración del entorno véase:

- [http://qt-project.org/wiki/Setting-up-Qt-Creator-for-BlackBerry-and-QNX](http://qt-project.org/wiki/Setting-up-Qt-Creator-for-BlackBerry-and-QNX)
- [https://developer.blackberry.com/native/documentation/core/qt_porting_tools.html](https://developer.blackberry.com/native/documentation/core/qt_porting_tools.html)


## Desarrollo del servidor

En el reporte anterior ya vimos como crear y registrar servicios en PHP usando NuSOAP, por ello vamos a mostrar únicamente lo esencial.

### El modelo de datos

Nuestra base de datos consiste de 4 tablas, Cliente, Producto, Pedido y Detalle.

![Modelo de datos](/report-iv-bb10-web-service/bbws_data_model.png)

**NOTA:** Con el código fuente incluyo el modelo de la base de datos, fue diseñado utilizando MySQL Workbench y por lo tanto podrán exportar la base de datos desde ahí.

### Los servicios

El web service no difiere mucho del que utilizamos en el proyecto anterior, se ha agregado el servicio _GetAllProducts_ y  el servicio _Synchronize_ ha sido reemplazado con _PutRegisters_.


```php
function GetAllProducts()
{
    $mysqli = OpenDB();
    $mysqli->query("SET NAMES UTF8");
    $query = "SELECT * FROM Producto";

    $result = $mysqli->query($query);
    $mysqli->close();
    if ($result->num_rows == 0) {
        return array();
    }

    $products = array();
    while ($row = $result->fetch_assoc()) {
        $products[] = array(
            'IdProduct' => $row['IdProducto'],
            'Description' => $row['Descripcion']
        );
    }

    return $products;
}


function PutRegisters($RequestItems, $DetailItems)
{
    if (is_array($RequestItems)) {
        $requests = to_request_array($RequestItems);
    } else {
        $requests = array();
    }

    if (is_array($DetailItems)) {
        $details = to_detail_array($DetailItems);
    } else {
        $details = array();
    }

    $mysqli = OpenDB();
    foreach ($requests as $r) {
        $idRequest = $r['IdRequest'];
        $requestIdClient = $r['IdClient'];
        $requestDate = $r['RequestDate'];

        if (findRequest($requestIdClient, $requestDate, $mysqli) == NOT_FOUND) {
            $newIdRequest = CreateRequest($requestIdClient, $requestDate,
                                          $mysqli);
            foreach ($details as $d) {
                $product = $d['IdProduct'];
                $amount = $d['Amount'];

                $detailIdRequest = $d['IdRequest'];
                if ($idRequest != $detailIdRequest) continue;

                CreateDetail($newIdRequest, $product, $amount, $mysqli);
            }
        }
    }

    $mysqli->close();

    return count($requests) + count($details);
}
```

La actualización de los datos con el servidor se ha simplificado puesto que ahora no tenemos que crear nuevos clientes.

## La base de datos local

Puesto que nuestra aplicación cliente deberá funcionar también en modo _offline_, debe existir una réplica del modelo de datos en el cliente. En esta ocasión utilizaremos SQLite. Las entidades son las siguientes:

<ul>
  <li>**Client** Representa a la tabla Cliente.</li>
  <li>**Request** Representa a la tabla Pedido.</li>
  <li>**Detail** Representa a la tabla Detalle.</li>
  <li>**Product** Representa a la tabla Detalle.</li>
  <li><del>**Key** Tabla auxiliar para almacenar las claves primarias de las tablas restantes.</del> Debido a las modificaciones ya no es necesaria.</li>
</ul>

### Inicialización de la base de datos

Cuando la aplicación inicia se debe preparar la base de datos, en caso de no existir ésta es creada. Dentro de la clase _Backend_ podrán encontrar el siguiente código:

```cpp
bool Backend::initDataBase()
{
    //removeDatabase(); return true;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setConnectOptions("foreign_key_constraints=ON");
    database.setDatabaseName(DB_PATH);

    if (!database.open()) {
        qDebug() << "ERROR: Could NOT open the database :(" << endl;
        return false;
    }

    this->sda = new SqlDataAccess(DB_PATH);
    sda->execute("PRAGMA foreign_keys = ON"); // FORCE foreign key constraints

    if (sda->hasError())
        qDebug() << "ERROR: " << sda->error() << endl;

    sda->execute(CREATE_TABLE_CLIENT);
    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    sda->execute(CREATE_TABLE_REQUEST);
    sda->execute(REQUEST_UNIQUE_CONSTRAINT);

    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    sda->execute(CREATE_TABLE_PRODUCT);
    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    sda->execute(CREATE_TABLE_DETAIL);
    sda->execute(DETAIL_UNIQUE_CONSTRAINT);
    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    return true;
}
```

### Operaciones con la base de datos

Para simplificar la lógica de la aplicación se crearon varias funciones auxiliares para las diferentes operaciones, como son insertar registros, consultas, etc.

Inserción de registros:

```cpp
bool Backend::insertClient(int id, QString name, QString middleName,
                           QString lastName, QString address)
{
    QVariantList client;
    client << id << name << middleName << lastName << address;
    QString values = QString("VALUES(%1, '%2', '%3', '%4', '%5')")
                     .arg(to_s(id), name, middleName, lastName, address);

    QString query = "INSERT INTO Client(IdClient, Name, MiddleName, "
                    " LastName, Address) " + values;

    sda->execute(query);
    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    return true;
}

bool Backend::insertProduct(int id, QString description)
{
    QString values = QString("VALUES(%1, '%2')").arg(to_s(id), description);
    sda->execute("INSERT INTO PRODUCT(IdProduct, Description) " + values);

    if (sda->hasError()) {
        qDebug() << "ERROR::: " << sda->error() << endl;
        return false;
    }

    return true;
}

int Backend::insertRequest(int idClient, QString date)
{
    QString values = QString("VALUES(%1, '%2')").arg(to_s(idClient), date);
    QString query = "INSERT INTO Request(IdClient, RequestDate) " + values;
    QSqlQuery Q = sda->connection().exec(query);
    //qDebug() << "LAST INSERTED ID: " << Q.lastInsertId().toInt() << endl;

    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return -1;
    }

    return Q.lastInsertId().toInt();
}

bool Backend::insertDetail(int idRequest, int idProduct, int amount)
{
    QString idr = to_s(idRequest);
    QString a = to_s(amount);
    QString p = to_s(idProduct);

    QString values = QString("VALUES(%1, %2, %3)").arg(idr, p, a);
    sda->execute("INSERT INTO Detail(IdRequest, IdProduct, Amount) " + values);

    if (sda->hasError()) {
        qDebug() << "ERROR: " << sda->error() << endl;
        return false;
    }

    return true;
}
```

Consulta de registros:

```cpp
QVector<Client> Backend::selectClients()
{
    QString query = "SELECT * FROM Client";
    QVariant result = sda->execute(query);
    QVariantList list = result.value<QVariantList>();
    int n = list.size();
    QVector<Client> clients;
    for (int i = 0; i < n; i++) {
        Client c;
        QVariantMap map = list.at(i).value<QVariantMap>();
        c.setIdClient(map["IdClient"].toString().toInt());
        c.setName(map["Name"].toString());
        c.setMiddleName(map["MiddleName"].toString());
        c.setLastName(map["LastName"].toString());
        c.setAddress(map["Address"].toString());
        clients.append(c);
    }
    return clients;
}

QVector<Product> Backend::selectProducts()
{
    QString query = "SELECT * FROM Product";
    QVariant result = sda->execute(query);
    QVariantList list = result.value<QVariantList>();
    int n = list.size();
    QVector<Product> products;
    for (int i = 0; i < n; i++) {
        Product p;
        QVariantMap map = list.at(i).value<QVariantMap>();
        p.setIdProduct(map["IdProduct"].toString().toInt());
        p.setDescription(map["Description"].toString());
        products.append(p);
    }

    return products;
}

QVector<Request> Backend::selectRequests()
{
    QString query = "SELECT * FROM Request";
    QVariant result = sda->execute(query);
    QVariantList list = result.value<QVariantList>();
    int n = list.size();
    QVector<Request> requests;
    for (int i = 0; i < n; i++) {
        Request r;
        QVariantMap map = list.at(i).value<QVariantMap>();
        r.setIdRequest(map["IdRequest"].toString().toInt());
        r.setIdClient(map["IdClient"].toString().toInt());
        r.setRequestDate(map["RequestDate"].toString());
        requests.append(r);
    }

    return requests;
}

QVector<Detail> Backend::selectDetails()
{
    QString query = "SELECT * FROM Detail";
    QVariant result = sda->execute(query);
    QVariantList list = result.value<QVariantList>();
    int n = list.size();
    QVector<Detail> details;
    for (int i = 0; i < n; i++) {
        QVariantMap map = list.at(i).value<QVariantMap>();
        Detail d;
        d.setIdDetail(map["IdDetail"].toString().toInt());
        d.setIdRequest(map["IdRequest"].toString().toInt());
        d.setIdProduct(map["IdProduct"].toString().toInt());
        d.setAmount(map["Amount"].toString().toInt());

        details.append(d);
    }

    return details;
}
```

Creo que no hay necesidad de explicar el código ya que se explica a sí mismo.

## Comunicación con el Web service

Qt no proporciona mucho soporte para trabajar con Web services (¿Me equivoco?) pero si lo necesario para comunicarnos con el servidor, para extraer los datos de los mensajes que nos regrese el servidor habrá que ensuciarnos las manos un poquito.

Vamos a ilustrar la comunicación con uno de los servicios, _GetAllClients_, el resto de las operaciones son similares. Primero creamos un método llamado _queryClients()_, el cual envía la solicitud al servidor con el mensaje adecuado:

```cpp
void Backend::queryClients()
{
    QUrl url(WS_URL);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply *)),
                     this, SLOT(getClientsFinished(QNetworkReply*)));
    networkManager->post(request, MSG_GET_ALL_CLIENTS.toAscii());
}
```

El valor de `WS_URL` en nuestro caso es `http://192.168.1.200/request_ws/index.php`, la constante `MSG_GET_ALL_CLIENTS` almacena el mensaje SOAP que solicita la lista de clientes:

```xml
<?xml version="1.0"?>
<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:req="Request">
  <soapenv:Header/>
  <soapenv:Body>
    <req:GetAllClients/>
  </soapenv:Body>
</soapenv:Envelope>
```

La comunicación con el servidor se realiza de manera asíncrona, el método que recibirá la respuesta del servidor es _getClientsFinished()_:

```cpp
void Backend::getClientsFinished(QNetworkReply *reply)
{
    QByteArray ans = reply->readAll();
    QString response(ans.data());
    QVector<Client> clients = toClientArray(response);
    int n = clients.size();
    for (int i = 0; i < n; i++) {
        insertClient(clients[i].idClient(),
                     clients[i].name(),
                     clients[i].middleName(),
                     clients[i].lastName(),
                     clients[i].address());
    }

    loadClientsToList();
}
```

El contenido de la variable _response_ almacena la respuesta del servidor en formato XML, por lo que hay que procesarla para obtener los datos que nos interesan, esto se realiza en el método _toClientArray()_, que devuelve una lista de clientes:

```cpp
QVector<Client> Backend::toClientArray(QString message)
{
    QVector<Client> list;
    Client client;
    QXmlStreamReader reader(message);
    while (!reader.atEnd()) {
        reader.readNext();
        QString name = reader.name().toString();
        if (name == "IdClient" || name == "Name" || name == "MiddleName" ||
                name == "LastName" || name == "Address") {
            QString value = reader.readElementText();

            if (name == "IdClient") {
                client.setIdClient(value.toInt());
            } else if (name == "Name") {
                client.setName(value);
            } else if (name == "MiddleName") {
                client.setMiddleName(value);
            } else if (name == "LastName") {
                client.setLastName(value);
            } else if (name == "Address") {
                client.setAddress(value);
                list.append(client);
            }
        }
    }

    return list;
}
```

En el código anterior nos apoyamos de la clase [QXmlStreamReader](https://qt-project.org/doc/qt-4.8/qxmlstreamreader.html) para extraer los valores.


## El cliente

Ahora veamos como crear una aplicación para BlackBerry que consuma nuestros servicios. El código es un poco extenso así que se explicarán únicamente las partes más importantes.

Hasta hace poco la tecnología empleada para crear aplicaciones BlackBerry era Java, sin embargo, en un intento por permanecer en el mercado, Blackberry ha apostado también por los dispositivos _touch_ y ha reemplazado Java por C++, la tecnología se conoce como [Cascades](http://developer.blackberry.com/native/), un framework basado en [Qt](https://www.qt.io/developers/) y [QML](http://qt-project.org/doc/qt-5.0/qtqml/qtqml-index.html)  para diseñar interfaces gráficas de manera nativa. 

### La página principal

Así lucirá la página principal de nuestra aplicación:

![Página principal de la aplicación](/report-iv-bb10-web-service/bbws_app_home.png)

El diseño de esta página en QML es el siguiente:

```javascript
Tab {
    title: "Inicio"
    imageSource: "asset:///pictures/home.png"
    NavigationPane {
        id: homeNavigationPane
        objectName: "homeNavigationPane"
        Page {
            id: home
            Container {
                layout: DockLayout { }

                Container {
                    verticalAlignment: VerticalAlignment.Top
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }

                    ImageView {
                        imageSource: "asset:///pictures/LogoITCH.png"
                    }

                    Label {
                        multiline: true
                        leftMargin: 50
                        textStyle {
                            fontSize: FontSize.Large
                        }
                        text:   "Desarrollo de Aplicaciones\npara Tecnologías Móviles"
                    }
                }

                Container {
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Fill

                    layout: StackLayout { }

                    Button {
                        text: "Enviar registros al servidor"
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            homeNavigationPane.push(progressPage)
                            backend.putRegisters()
                        }
                    }

                    Button {
                        text: "Limpiar registros y actualizar catálogos"
                        horizontalAlignment: HorizontalAlignment.Fill
                        onClicked: {
                            homeNavigationPane.push(progressPage)
                            backend.updateCatalogs()
                        }
                    }

                }


            }
        }

    }
}
```

### Registro de pedidos

La siguiente imagen muestra la interfaz de usuario para registrar nuevos pedidos.

![Registro de pedidos](/report-iv-bb10-web-service/bbws_app_shop.png)

El diseño de la interfaz en QML es el siguiente:

```javascript
Tab {
    title: "Pedidos"
    imageSource: "asset:///pictures/shop.png"

    NavigationPane {
        id: requestNavigationPane
        objectName: "requestNavigationPane"
        Page {
            Container {
                layout: StackLayout { }

                DropDown {
                    horizontalAlignment: HorizontalAlignment.Fill
                    title: "Cliente"
                    objectName: "clientList"
                    id: clientList
                    enabled: true

                }

                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 4
                    }

                    ListView {
                        objectName: "newItems"
                        listItemComponents: ListItemComponent {
                            type: "item"

                            Container {
                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }

                                    Label {
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 1
                                        }

                                        text: ListItemData.amount
                                    }

                                    Label {
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 6
                                        }

                                        text: ListItemData.description
                                    }

                                }

                                Divider {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                }
                            }

                        }
                    }
                }

                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }

                    DropDown {
                        objectName: "productList"
                        id: productList
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 6
                        }
                        title: "Producto"
                        enabled: true

                    }

                    TextField {
                        id: itemAmount
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 2
                        }
                        hintText: "Cantidad"
                    }

                    Button {
                        attachedObjects: [
                            SystemToast {
                                id: productToast
                                body: "Seleciona un producto."
                            }
                        ]

                        imageSource:"asset:///pictures/add.png"
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }
                        onClicked: {
                            var selectedOption = productList.selectedOption
                            if (selectedOption  !== null) {
                                var idProduct = selectedOption.value
                                var description = selectedOption.text
                                console.log("IdProduct = " + idProduct)
                                var ok = backend.addDetail(idProduct, description, itemAmount.text)
                                if (ok) {
                                    itemAmount.text = ""
                                    productList.resetSelectedOption()
                                }
                            } else {
                                productToast.show()
                            }
                        }
                    }
                }

                Button {
                    attachedObjects: [
                        SystemToast {
                            id: clientToast
                            body: "No hay nada que guardar."
                        }
                    ]

                    horizontalAlignment: HorizontalAlignment.Fill
                    text: "Guardar pedido"
                    onClicked: {
                        var selectedOption = clientList.selectedOption
                        if (selectedOption !== null) {
                            var idClient = selectedOption.value
                            console.log("IdClient = " + idClient)
                            var ok = backend.saveRequest(idClient)
                            if (ok) {
                                idClient.text = ""
                                clientList.resetSelectedOption()
                            }
                        } else {
                            clientToast.show()
                        }
                    }
                }
            }
        }
    }
}
```

Cuando el usuario presiona el botón para guardar el pedido, se invoca al método _saveReqeust()_ de la clase Backend con el ID del cliente para que almacene el pedido en la base de datos, la lista de artículos artículos se almacena en la clase Backend, por lo que no hay necesidad de enviársela. Aquí el código:

```cpp
bool Backend::saveRequest(QString idClient)
{
    int idc = idClient.toInt();

    if (_newDetails->isEmpty()) {
        toast->setBody("Debe haber al menos un artículo.");
        toast->show();
        return false;
    }


    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString year    = to_s(date.year());
    QString month   = to_s(date.month());
    QString day     = to_s(date.day());
    QString hour    = to_s(time.hour());
    QString minute  = to_s(time.minute());
    QString second  = to_s(time.second());
    QString rightNow = year + "-" + month + "-" + day + " "
                     + hour + ":" + minute + ":" + second;

    Key keys = getKeys();
    int idr = keys.newIdRequest();
    if (!insertRequest(idr, idc, rightNow))
        return false;

    int n = _newDetails->size();
    for (int i = 0; i < n; i++) {
        keys = getKeys();
        int idd = keys.newIdDetail();
        int idProduct = _newDetails->at(i).idProduct();
        int amount = _newDetails->at(i).amount();
        if (!insertDetail(idd, idr, idProduct, amount))
            return false;
    }


    toast->setBody("¡Exito!");
    toast->show();
    _newDetails->clear();
    _newDetailsModel->clear();
    return true;
}
```

### Consulta de pedidos

Nuestra aplicación también permite consultar la lista de pedidos, aquí la interfaz:

![Consulta de pedidos](/report-iv-bb10-web-service/bbws_app_query.png)

El diseño en QML es el siguiente:

```javascript
Tab {
    imageSource: "asset:///pictures/search.png"
    Page {
        id: queryPage
        paneProperties: NavigationPaneProperties {
            backButton: ActionItem {
                onTriggered: {
                    requestNavigationPane.pop()
                }
            }
        }

        Container {
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                Label {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 5
                    }

                    text: "Lista de pedidos"
                }

                Button {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                    imageSource: "asset:///pictures/refresh.png"
                    onClicked: {
                        backend.loadRequestsToList()
                    }
                }

            }

            ListView {
                objectName: "listOfRequests"
                listItemComponents: ListItemComponent {
                    type: "item"

                    Container {
                        layout: StackLayout { }

                        Container {
                            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                            Label {
                                layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                            }

                            Label {
                                layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                                text: ListItemData.amount
                            }

                            Label {
                                layoutProperties: StackLayoutProperties { spaceQuota: 6 }
                                text: ListItemData.description
                            }
                        }

                        Divider {
                            horizontalAlignment: HorizontalAlignment.Fill
                        }
                    }
                }
            }
        }
    }
}
```

La lógica detrás de esta operación se encuentra en el método _loadRequestsToList()_:

```cpp
void Backend::loadRequestsToList()
{
    QString query = "SELECT Request.IdRequest, Client.Name, Client.MiddleName, "
                    "Client.LastName, Product.Description, Detail.Amount, "
                    "Request.RequestDate FROM Request, Client, Detail, Product "
                    "WHERE Detail.IdRequest = Request.IdRequest AND "
                    "Request.IdClient = Client.IdClient AND "
                    "Detail.IdProduct = Product.IdProduct";
    QVariant result = sda->execute(query);
    if (sda->hasError()) {
        qDebug() << "ERROR: "  << sda->error() << endl;
    }

    QVariantList list = result.value<QVariantList>();

    int n = list.size();
    _requestModel->clear();

    QVariantMap entry;
    QVariantMap row;
    for (int i = 0; i < n; i++) {
        row = list.at(i).value<QVariantMap>();
        QString id = row["IdRequest"].toString();
        QString client  = row["Name"].toString() + " "
                        + row["MiddleName"].toString() + " "
                        + row["LastName"].toString();
        QString date = row["RequestDate"].toString();

        entry["Request"] = id + ": " + client + " (" + date + ")";

        entry["description"] = row["Description"].toString();
        entry["amount"] = row["Amount"].toString();

        _requestModel->insert(entry);
    }
}
```

El objeto *_requestModel* esta **enlazado** a un objeto [ListView](http://developer.blackberry.com/native/reference/cascades/bb__cascades__listview.html) en la interfaz gráfica, por lo que los cambios que le ocurren al objeto *_requestModel* se reflejan automáticamente en el ListView.

### Subir los registros al servidor

Para esta operación solo tenemos que presionar un botón y se nos mostrará una barra de progreso que simulará el progreso de la operación.

![Envío de pedidos al servidor](/report-iv-bb10-web-service/bbws_app_upload.png)

El código que realiza esta operación es el siguiente:

```cpp
void Backend::putRegisters()
{
    QUrl url(WS_URL);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(putRequestsFinished(QNetworkReply*)));
    networkManager->post(request, formattedRegisters().toAscii());
    _progressMessage->setText("Enviando registros...");
    _progressIndicator->setValue(50);
}
```

El método _formattedRegisters()_ consulta los registros necesario y los estructura en un formato SOAP para que el servidor pueda interpretar los datos que le enviamos:

```cpp
QString Backend::formattedRegisters()
{
    QString header = "<soapenv:Envelope "
                     "xmlns:soapenv='http://schemas.xmlsoap.org/soap/envelope/'"
                     " xmlns:req='Request'> <soapenv:Header/> <soapenv:Body> "
                     " <req:PutRegisters>";

    QString footer = "</req:PutRegisters> </soapenv:Body> </soapenv:Envelope>";

    QString requests = "\n";
    requests += "<RequestItems>";
    requests += "\n";

    QVector<Request> R = selectRequests();
    int n = R.size();
    for (int i = 0; i < n; i++) {
        requests += "<item>";
        requests += "<IdRequest>" + to_s(R[i].idRequest()) + "</IdRequest>";
        requests += "<IdClient>" + to_s(R[i].idClient())+ "</IdClient>";
        requests += "<RequestDate>" + R[i].requestDate() + "</RequestDate>";
        requests += "</item>";
        requests += "\n";
    }
    requests += "</RequestItems>";

    QString details = "<DetailItems>";
    details += "\n";
    QVector<Detail> D = selectDetails();
    n = D.size();
    for (int i = 0; i < n; i++) {
        details += "<item>";
        details += "<IdDetail>" + to_s(D[i].idDetail()) + "</IdDetail>";
        details += "<IdRequest>" + to_s(D[i].idRequest()) + "</IdRequest>";
        details += "<IdProduct>" + to_s(D[i].idProduct()) + "</IdProduct>";
        details += "<Amount>" + to_s(D[i].amount()) + "</Amount>";
        details += "</item>";
        details += "\n";
    }
    details += "</DetailItems>";


    QString message = header + requests + "\n" + details + "\n" + footer;
    return message;
}
```

La actualización de catálogos es muy similar.

![Actualización de catálogos](/report-iv-bb10-web-service/bbws_app_download.png)

Como lo indica el texto del botón, esta operación borra los registros de la base de datos local y actualiza los catálogos con el servidor, he aquí el código:

```cpp
void Backend::updateCatalogs()
{
    removeDatabase();
    _progressMessage->setText("Limpiando registros");
    _progressIndicator->setValue(25);
    initDataBase();

    _progressMessage->setText("Descargando catalogo de clientes...");
    _progressIndicator->setValue(50);
    queryClients();
    _progressMessage->setText("Descargando catalogo de clientes...");
    _progressIndicator->setValue(75);
    queryProducts();
}
```

La operación _queryClients()_ ya la vimos anteriormente cuando explicamos la comunicación con el Web service, solo falta mostrar como se obtiene la lista de productos:

```javascript
void Backend::queryProducts()
{
    QUrl url(WS_URL);
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply *)),
                     this, SLOT(getProductsFinished(QNetworkReply*)));
    networkManager->post(request, MSG_GET_ALL_PRODUCTS.toAscii());
}

void Backend::getProductsFinished(QNetworkReply *reply)
{
    QByteArray ans = reply->readAll();
    QString response(ans.data());
    QVector<Product> products = toProductArray(response);

    int n = products.size();
    for (int i = 0; i < n; i++) {
        insertProduct(products[i].idProduct(), products[i].description());
    }

    loadProductsToList();
}
```


Y bueno, mi intención  no es abrumarlos con mucho código, creo que las partes más importantes ya se han explicado. Al final se proporciona el código completo para que prueben la aplicación si así lo desean.


## Código fuente

El código tanto del cliente como del servidor están disponibles en Bitbucket en las siguientes direcciones:

[https://bitbucket.org/rendon/request_ws](https://bitbucket.org/rendon/request_ws)
[https://bitbucket.org/rendon/requisition_bb10](https://bitbucket.org/rendon/requisition_bb10)

O bien pueden clonar los proyectos:

```
$ git clone https://rendon@bitbucket.org/rendon/request_ws.git
$ git clone https://rendon@bitbucket.org/rendon/requisition_bb10.git
```

La licencia del Web service y del la aplicación cliente es GPLv3.

## Por hacer

Esta es la primara vez que utilizo Qt para algo más que un simple "Hola, mundo!", y la primera vez que utilizo QML, seguramente existe una mejor manera de realizar las cosas, Qt emplea el patrón de diseño [Model View](http://qt-project.org/doc/qt-4.8/modelview.html), sin embargo, al ser la primera vez, me enfoque más en que las cosas funcionaran. Lo cierto es que apegarse a un patrón de diseño ayuda a dar mantenimiento a nuestro software de forma más fácil.

## Referencias

- [Documentación de Cascades](http://developer.blackberry.com/native/documentation/cascades/)
- [Documentación de Qt](https://www.qt.io/developers/)
