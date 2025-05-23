<!-- vim: set spelllang=es_MX: -->

---
tags:
    - dev
    - web-services
    - post
created: 2016-02-24
updated: 2024-05-06
---
# Reporte III: Windows Phone 8 & Web services

Tengo que decir que no soy un usuario Windows, pero en esta situación no tuve elección.

Este reporte corresponde al proyecto número 3 de la asignatura Desarrollo de Aplicaciones para Tecnologías Móviles.

## Definición del problema

Este proyecto consiste en lo siguiente:

<blockquote>Desarrollar un Web service (en el lenguaje que más les agrade) capaz de manipular una base de datos a petición del cliente, en este caso, el cliente será una aplicación móvil para la plataforma Windows Phone 8.</blockquote>

## Definiciones

Como este reporte forma parte de una serie de reportes, vamos a omitir la teoría sobre Web services puesto que ya se abordo en el reporte número [II](/report-ii-microoj-web-services).

## Propuesta de solución

Nuevamente, el problema nos da la flexibilidad de elegir que problema modelar, la propuesta es la siguiente:

</blockquote>Desarrollar una aplicación móvil para el control requisiciones, similar a los dispositivos que utilizan los agentes de venta cuando salen a levantar pedidos.</blockquote>

### El cliente

La aplicación móvil deberá cumplir con los siguientes requisitos:

<ul>
  <li>La aplicación permitirá registrar clientes a la base de datos.</li>
  <li>La aplicación permitirá consultar la lista de clientes.</li>
  <li>La aplicación permitirá registrar pedidos.</li>
  <li>La aplicación permitirá consultar la lista de pedidos.</li>
  <li>La aplicación deberá tener la capacidad de trabajar tanto _online_ como _offline_.</li>
  <li>La aplicación permitirá sincronizar los datos con el servidor.</li>
</li>

### El servidor

Un Web service desarrollado en PHP que manipula una base de datos MySQL.

A continuación la lista de servicios que vamos desarrollar:

<ul>
  <li>**Synchronize(clients[], requests[], details[])** Recibe los datos de la aplicación móvil y realiza la sincronización.</li>
  <li>**GetAllClients()** Retorna al cliente la lista de clientes. Este servicio forma parte de la sincronización.</li>
  <li>**GetAllRequests()** Retorna al cliente la lista de peticiones. Este servicio forma parte de la sincronización.</li>
  <li>**GetAllDetails()** Retorna al cliente la lista de detalles de cada petición. Este servicio forma parte de la sincronización.</li>
</ul>

## Requisitos

Para poder realizar esta práctica se necesita lo siguiente:

<ul>
  <li>Un servidor WAMP (Windows + Apache + MySQL + PHP), [http://www.wampserver.com/en/](http://www.wampserver.com/en/).</li>
  <li>Visual Studio 2012 Professional</li>
  <li>Windows Phone 8 SDK ([http://dev.windowsphone.com/en-us/downloadsdk](http://dev.windowsphone.com/en-us/downloadsdk))</li>
</ul>

Considero que es algo básico y no hay necesidad de explicar como instalar estas herramientas. Si es el caso, quizás aun no es el momento para seguir esta práctica.

## Desarrollo del servidor

En el reporte anterior ya vimos como crear y registrar servicios en PHP usando NuSOAP, por ello vamos a mostrar únicamente lo esencial.

### El modelo de datos

Nuestra base de datos consiste de 3 tablas, Cliente, Pedido y Detalle.

![El modelo de datos](/report-iii-wp8-web-services/ws_wp8_01.png)

**NOTA:** Con el código fuente incluyo el modelo de la base de datos, fue diseñado utilizando MySQL Workbench y por lo tanto podrán exportar la base de datos desde ahí.

### Synchronize

```
function Synchronize($ClientItems, $RequestItems, $DetailItems)
{
    if (is_array($ClientItems)) {
        $clients = to_client_array($ClientItems);
    } else {
        $clients = array();
    }

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
    foreach ($clients as $c) {
        $idClient = $c['IdClient'];
        $name = $c['Name'];
        $middleName = $c['MiddleName'];
        $lastName = $c['LastName'];
        $address = $c['Address'];
        if (findClient($name, $middleName, $lastName,
                       $address, $mysqli) == NOT_FOUND) {

           $newIdClient = CreateClient($name, $middleName, $lastName,
                                       $address, $mysqli);
            foreach ($requests as $r) {
                $idRequest = $r['IdRequest'];
                $requestIdClient = $r['IdClient'];
                $requestDate = $r['RequestDate'];

                if ($requestIdClient != $idClient)
                    continue;

                $requestIdClient = $newIdClient;
                $newIdRequest = CreateRequest($requestIdClient, $requestDate,
                                              $mysqli, $mysqli);
                foreach ($details as $d) {
                    $item = $d['Item'];
                    $amount = $d['Amount'];

                    $detailIdRequest = $d['IdRequest'];
                    if ($idRequest != $detailIdRequest) continue;
                    CreateDetail($newIdRequest, $item, $amount, $mysqli);
                }
            }
        } else {
            foreach ($requests as $r) {
                $idRequest = $r['IdRequest'];
                $requestIdClient = $r['IdClient'];
                $requestDate = $r['RequestDate'];

                if ($requestIdClient != $idClient)
                    continue;
                
                if (findRequest($requestIdClient, $requestDate,
                                $mysqli) == NOT_FOUND) {
                    $newIdRequest = CreateRequest($requestIdClient, 
                                                  $requestDate, $mysqli);
                    foreach ($details as $d) {
                        $item = $d['Item'];
                        $amount = $d['Amount'];

                        $detailIdRequest = $d['IdRequest'];
                        if ($idRequest != $detailIdRequest) continue;
                        CreateDetail($newIdRequest, $item, $amount, $mysqli);
                    }
                }
            }
        }
    }

    $mysqli->close();

    return count($clients) + count($requests) + count($details);
}
```
Los argumentos de esta función son arreglos. Algo curioso que me encontré es que estos arreglos deben tener más de un elemento para que PHP los reconozca como tal, por ello, lo primero que hacemos es convertir la entrada a un formato conveniente.

Lo que sigue es realizar la sincronización. Esta parte me resulto interesante y al parecer es un tema complicado. Mi algoritmo es muy sencillo y no esta optimizado, pero funciona (más me vale :) ).

<ul>
    <li>1 Para cada cliente que en la lista que recibimos, verificamos si ya existe en la base de datos:
        <ul>
            <li>1.1 Si el cliente no existe, entonces metemos a la base de datos todo lo relacionado a él, los pedidos con sus detalles.</li>
            <li>1.2 Si ya existe, entonces para cada uno de sus pedidos verificamos si ya se encuentra en la base de datos:
                <ul>
                    <li>1.2.1 Si el pedido no existe entonces metemos el pedido junto con sus detalles a la base de datos.</li>
                </ul>
            </li>
        </ul>
    </li>
</ul>

Nuestra aplicación móvil no permite modificar detalles de los pedidos, por lo tanto, en el algoritmos anterior no necesitamos verificar hasta los detalles.

El servicio se registra de la siguiente manera:

```
$server->register('Synchronize',
    array(
        'ClientItems' => 'tns:ArrayOfClient',
        'RequestItems' => 'tns:ArrayOfRequest',
        'DetailItems' => 'tns:ArrayOfDetail'),
    array('id' => 'xsd:integer'),
    'Request',
    false,
    'rpc',
    'literal',
    'Synchronize the user data with the server data'
);
```

### GetAllClients

Después de que la aplicación móvil manda los datos al servidor para la sincronización, ésta borra su base de datos y la vuelve a construir pero ahora con los datos del servidor. Quizás no lo más adecuado pero si lo más fácil.

```
function GetAllClients()
{
    $mysqli = OpenDB();
    $mysqli->query("SET NAMES UTF8");
    $query = "SELECT * FROM Cliente";

    $result = $mysqli->query($query);
    $mysqli->close();
    if ($result->num_rows == 0) {
        return array();
    }

    $clients = array();
    while ($row = $result->fetch_assoc()) {
        $clients[] = array(
            'IdClient' => $row['IdCliente'],
            'Name' => $row['Nombre'],
            'MiddleName' => $row['ApellidoPaterno'],
            'LastName' => $row['ApellidoMaterno'],
            'Address' => $row['Domicilio']);
    }

    return $clients;
}
```

El servicio se registra de la siguiente manera:

```
$server->register('GetAllClients',
    array(),
    array('clients' => 'tns:ArrayOfClient'),
    'Request',
    false,
    'rpc',
    'literal',
    'Retrieve all clients.'
);
```

### GetAllRequests

El código para este servicio es el siguiente:

```
function GetAllRequests()
{
    $mysqli = OpenDB();
    $mysqli->query("SET NAMES UTF8");
    $query = "SELECT * FROM Pedido";

    $result = $mysqli->query($query);
    $mysqli->close();
    if ($result->num_rows == 0) {
        return array();
    }

    $requests = array();
    while ($row = $result->fetch_assoc()) {
        $requests[] = array(
            'IdRequest' => $row['IdPedido'],
            'IdClient' => $row['IdCliente'],
            'RequestDate' => $row['Fecha']);
    }

    return $requests;
}
```

Y el registro del servicio es el siguiente:

```
$server->register('GetAllRequests',
    array(),
    array('requests' => 'tns:ArrayOfRequest'),
    'Request',
    false,
    'rpc',
    'literal',
    'Retrieve all requests.'
);
```

### GetAllDetails

El código es similar a los dos anteriores:

```
function GetAllDetails()
{
    $mysqli = OpenDB();
    $mysqli->query("SET NAMES UTF8");
    $query = "SELECT * FROM Detalle";

    $result = $mysqli->query($query);
    $mysqli->close();
    if ($result->num_rows == 0) {
        return array();
    }

    $details = array();
    while ($row = $result->fetch_assoc()) {
        $details[] = array(
            'IdDetail' => $row['IdDetalle'],
            'IdRequest' => $row['IdPedido'],
            'Item' => $row['Articulo'],
            'Amount' => $row['Cantidad']
        );
    }

    return $details;
}
```

Y su respectivo registro:

```
$server->register('GetAllDetails',
    array(),
    array('details' => 'tns:ArrayOfDetail'),
    'Request',
    false,
    'rpc',
    'literal',
    'Retrieve all details.'
);
```

Al final se proporciona el código fuente completo.

## La base de datos local

Puesto que nuestra aplicación cliente deberá funcionar también en modo _offline_, debe existir una réplica del modelo de datos en el cliente. Para ello vamos a utilizar lo que se conoce como **LINQ to SQL**, una tecnología que permite trabajar con tablas en forma de clases.

Las clases que representan a la base de datos local son las siguientes:

<ul>
  <li>**Client** Representa a la tabla Cliente (o sea, obvio :) )</li>
  <li>**Request** Representa a la table Pedido.</li>
  <li>**Detail** Representa a la tabla Detalle.</li>
  <li>**Key** Tabla auxiliar para almacenar las claves primarias de las tablas restantes.</li>
</ul>

Las claves primarias de la base de datos del servidor son de tipo _autoincrement_, sin embargo, para poder realizar la sincronización fue necesario hacer algunos ajustes, digamos que las claves primarias de la base de datos local **no son** autoincrement, por ello la necesida de la tabla _Key_.

El código de las clases es simple, aunque algo extenso. Por ello no lo vamos a listar aquí.

Para construir la base de datos a partir de las clases vamos a utilizar la clase `DataContext`. El siguiente código arma la base de datos:

```
    public class RequisitionDataContext : DataContext
    {
        public static string DBConnectionString =
            "Data Source=isostore:/Requisitions.sdf";
        public RequisitionDataContext(string connectionString)
            : base(connectionString)
        { }

        public Table<Client> clients;
        public Table<Detail> details;
        public Table<Request> requests;
        public Table<Key> keys;
    }
```

La estructura de la base de datos ya esta, pero aun no ha sido creada, eso lo realizaremos en el momento que la aplicación inicie su ejecución. En el archivo _App.xaml.cs_, al final del constructor pegamos el siguiente código:

```
string cs = RequisitionDataContext.DBConnectionString;
using(RequisitionDataContext db = new RequisitionDataContext(cs))
{
    if (!db.DatabaseExists())
    {
        db.CreateDatabase();
    }

    // db.DeleteDatabase();
}
```

Creamos la base de datos solo en caso de que no haya sido creada aún.

El resto de las operaciones se describirán en la siguiente sección.

## Desarrollo del cliente

En este apartado vamos a ver a grandes rasgos cómo esta compuesta nuestra aplicación móvil.

### Creación del proyecto

Bien, lo primero es crear el proyecto: File -> New Project -> C# -> Windows Phone 8.

A continuación se muestra como debe lucir la estructura del proyecto (en la imagen se muestra la estructura final):

![Nuestro proyecto en el Explorador de soluciones](/report-iii-wp8-web-services/ws_wp8_02.png)

Mi intención era emplear el patrón de diseño MVVM pero al parecer termine implementando la lógica en la parte del View. Será para la próxima.

### Conexión al Web service

Visual Studio tiene la opción de generar el código fuente necesario para comunicarnos con un Web service, vamos al explorador de soluciones, click derecho sobre nuestro proyecto, elegimos la opción "Add service reference", nos aparecerá la siguiente ventana:

![Conexión al Web service](/report-iii-wp8-web-services/ws_wp8_03.png)


### La pagina principal

La siguiente imagen muestra la pagina principal de la aplicación:

![Pagina principal](/report-iii-wp8-web-services/ws_wp8_04.png)

El diseño correspondiente en XAML (archivo _MainPage.xaml_):

```
<!--LayoutRoot is the root grid where all page content is placed-->
<Grid x:Name="LayoutRoot" Background="Transparent">
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto"/>
        <RowDefinition Height="*"/>
    </Grid.RowDefinitions>

    <!--TitlePanel contains the name of the application and page title-->
    <StackPanel x:Name="TitlePanel" Grid.Row="0" Margin="12,17,0,28">
        <TextBlock Text="Control de Requisiciones" Style="{StaticResource PhoneTextNormalStyle}" Margin="12,0"/>
        <TextBlock Text="Inicio" Margin="9,-7,0,0" Style="{StaticResource PhoneTextTitle1Style}"/>
    </StackPanel>

    <!--ContentPanel - place additional content here-->
    <Grid x:Name="ContentPanel" Grid.Row="1" Margin="12,0,12,0">
        <TextBlock HorizontalAlignment="Left" Margin="10,10,0,0" TextWrapping="Wrap" VerticalAlignment="Top" Height="515" Width="436" FontSize="36">
            <Run Text="Para realizar una operación utiliza los botones en la barra de aplicación."/>
            <LineBreak/>
            <LineBreak/>
            <LineBreak/>
            <LineBreak/>
            <LineBreak/>
            <LineBreak/>
            <LineBreak/>
            <Run Text="       DATM: Ags - Dic. 2013"/>
        </TextBlock>

    </Grid>

</Grid>

<phone:PhoneApplicationPage.ApplicationBar>
    <shell:ApplicationBar IsVisible="True" IsMenuEnabled="True">
        <shell:ApplicationBarIconButton 
            IconUri="/Images/UserAdd.png" 
            Text="Agregar" 
            x:Name="addClientButton" 
            Click="addClientButton_Click_1"
            />

        <shell:ApplicationBarIconButton 
            IconUri="/Images/UserFind.png" 
            Text="Consultar" 
            x:Name="queryClientButton" 
            Click="queryClientButton_Click_1"
            />


        <shell:ApplicationBarIconButton 
            IconUri="/Images/Shop.png" 
            Text="Pedido" 
            x:Name="shopButton" 
            Click="shopButton_Click_1"
            />

        <shell:ApplicationBarIconButton 
            IconUri="/Images/ShopFind.png" 
            Text="Consulta" 
            x:Name="queryShopButton" 
            Click="queryShopButton_Click_1"
            />


        <shell:ApplicationBar.MenuItems>
            <shell:ApplicationBarMenuItem x:Name="syncOperation"
                Text="sincronizar con el servidor"
                                           Click="syncOperation_Click_1" />
        </shell:ApplicationBar.MenuItems>


    </shell:ApplicationBar>
</phone:PhoneApplicationPage.ApplicationBar>
```



### Alta de clientes

La siguiente imagen muestra la interfaz para dar de alta a los clientes.

![Alta de clientes](/report-iii-wp8-web-services/ws_wp8_05.png)

El diseño correspondiente en XAML (archivo _View/AddClientView.xaml_):

```
<!--LayoutRoot is the root grid where all page content is placed-->
<Grid x:Name="LayoutRoot" Background="Transparent">
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto"/>
        <RowDefinition Height="*"/>
    </Grid.RowDefinitions>

    <!--TitlePanel contains the name of the application and page title-->
    <StackPanel Grid.Row="0" Margin="12,17,0,28">
        <TextBlock Text="Control de Requisiciones" Style="{StaticResource PhoneTextNormalStyle}"/>
        <TextBlock Text="Nuevo cliente" Margin="9,-7,0,0" Style="{StaticResource PhoneTextTitle1Style}" FontSize="48"/>
    </StackPanel>

    <!--ContentPanel - place additional content here-->
    <Grid x:Name="ContentPanel" Grid.Row="1" Margin="12,0,12,0">
        <TextBlock HorizontalAlignment="Left" 
                   Margin="29,15,0,0" 
                   TextWrapping="Wrap" 
                   Text="Nombre:" 
                   FontWeight="Bold"
                   VerticalAlignment="Top"/>
        <TextBox x:Name="nameText" 
                 Text="{Binding Client.Name, Mode=TwoWay}" 
                 HorizontalAlignment="Left" 
                 Height="72" 
                 Margin="10,42,0,0" 
                 TextWrapping="Wrap" 
                 VerticalAlignment="Top" 
                 Width="436"/>

        <TextBlock HorizontalAlignment="Left" 
                   Margin="29,124,0,0" 
                   TextWrapping="Wrap" 
                   Text="Apellido Paterno:" 
                   FontWeight="Bold"
                   VerticalAlignment="Top"/>
        <TextBox x:Name="middleNameText" 
                 Text="{Binding Client.MiddleName, Mode=TwoWay}" 
                 HorizontalAlignment="Left" 
                 Height="72" 
                 Margin="10,151,0,0" 
                 TextWrapping="Wrap" 
                 VerticalAlignment="Top" 
                 Width="436"/>

        <TextBlock HorizontalAlignment="Left" 
                   Margin="29,233,0,0" 
                   TextWrapping="Wrap" 
                   Text="Apellido Materno:" 
                   VerticalAlignment="Top" 
                   FontWeight="Bold"
                   Width="181"/>
        <TextBox x:Name="lastNameText" 
                 Text="{Binding Client.LastName, Mode=TwoWay}" 
                 HorizontalAlignment="Left" 
                 Height="72" 
                 Margin="10,260,0,0" 
                 TextWrapping="Wrap" 
                 VerticalAlignment="Top" 
                 Width="436"/>

        <TextBlock HorizontalAlignment="Left" 
                   Margin="29,342,0,0" 
                   TextWrapping="Wrap" 
                   Text="Domicilio:" 
                   VerticalAlignment="Top" 
                   FontWeight="Bold"
                   Width="96"/>
        <TextBox x:Name="addressText" 
                 Text="{Binding Client.Address, Mode=TwoWay}" 
                 HorizontalAlignment="Left" 
                 Height="183" Margin="10,369,0,0" 
                 TextWrapping="Wrap" 
                 VerticalAlignment="Top" 
                 Width="436"/>

        <Button Content="Crear" 
                HorizontalAlignment="Left" 
                Margin="341,557,0,0" 
                VerticalAlignment="Top" 
                Click="Button_Click_1"  />
    </Grid>
</Grid>
```

El código que se encarga de crear el nuevo cliente es el siguiente:

```
private void Button_Click_1(object sender, RoutedEventArgs e)
{
    if (String.IsNullOrEmpty(Client.Name) ||
        String.IsNullOrEmpty(Client.MiddleName) ||
        String.IsNullOrEmpty(Client.LastName) ||
        String.IsNullOrEmpty(Client.Address))
    {
        MessageBox.Show("ERROR: Te faltan dados.");
        return;
    }

    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        var keys = (from Key k in db.keys select k).First();
        Client newClient = new Client
        {
            IdClient = keys.NewIdClient,
            Name = Client.Name,
            MiddleName = Client.MiddleName,
            LastName = Client.LastName,
            Address = Client.Address
        };

        keys.NewIdClient += 1;
        db.clients.InsertOnSubmit(newClient);

        bool ok = true;
        try
        {
            db.SubmitChanges();
        }
        catch (Exception) { ok = false; }

        if (ok)
        {
            MessageBox.Show("El cliente ha sido agregado.");
            Client.Name = String.Empty;
            Client.MiddleName = String.Empty;
            Client.LastName = String.Empty;
            Client.Address = String.Empty;
        }
    }
}
```


### Consulta de Clientes

La siguiente imagen muestra la interfaz para la consulta de clientes.

![Consulta de clientes](/report-iii-wp8-web-services/ws_wp8_06.png)

El diseño correspondiente en XAML (archivo _View/QueryClientView.xaml_):

```
<!--LayoutRoot is the root grid where all page content is placed-->
<Grid x:Name="LayoutRoot" Background="Transparent">
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto"/>
        <RowDefinition Height="*"/>
    </Grid.RowDefinitions>

    <!--TitlePanel contains the name of the application and page title-->
    <StackPanel Grid.Row="0" Margin="12,17,0,28">
        <TextBlock Text="Control de Requisiciones" Style="{StaticResource PhoneTextNormalStyle}"/>
        <TextBlock Text="Consulta clientes" Margin="9,-7,10,0" Style="{StaticResource PhoneTextTitle1Style}" Height="73" FontSize="48"/>
    </StackPanel>

    <!--ContentPanel - place additional content here-->
    <Grid x:Name="ContentPanel" Grid.Row="1" Margin="12,0,12,0">
        <ListBox x:Name="queryResultList" ItemsSource="{Binding ClientItems}">
            <ListBox.ItemTemplate>
                <DataTemplate>
                    <StackPanel>
                        <Grid HorizontalAlignment="Stretch" Width="440" >
                            <Grid.ColumnDefinitions>
                                <ColumnDefinition Width="170" />
                                <ColumnDefinition Width="*" />
                            </Grid.ColumnDefinitions>
                            <Grid.RowDefinitions>
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                            </Grid.RowDefinitions>

                            <TextBlock Text="ID:" 
                                       Grid.Row="0" 
                                       Grid.Column="0" 
                                       FontWeight="Bold"
                                       VerticalAlignment="Center" />
                            <TextBlock Text="{Binding IdClient}" 
                                       Grid.Row="0" 
                                       Grid.Column="1" />

                            <TextBlock Text="Nombre:" 
                                       Grid.Row="1" 
                                       Grid.Column="0" 
                                       FontWeight="Bold"
                                       VerticalAlignment="Center" />
                            <TextBlock Text="{Binding Name}" 
                                       Grid.Row="1" 
                                       Grid.Column="1" />

                            <TextBlock Text="A. Paterno:" 
                                       Grid.Row="2" 
                                       Grid.Column="0" 
                                       FontWeight="Bold"
                                       VerticalAlignment="Center" />
                            <TextBlock Text="{Binding MiddleName}" 
                                       Grid.Row="2" 
                                       Grid.Column="1" />

                            <TextBlock Text="A. Materno:" 
                                       Grid.Row="3" 
                                       Grid.Column="0" 
                                       FontWeight="Bold"
                                       VerticalAlignment="Center" />
                            <TextBlock  Text="{Binding LastName}" 
                                        Grid.Row="3" 
                                        Grid.Column="1" />

                            <TextBlock 
                                       Text="Dirección:" 
                                       Grid.Row="4" 
                                       Grid.Column="0" 
                                       FontWeight="Bold"
                                       VerticalAlignment="Center" />
                            <TextBlock  Text="{Binding Address}" 
                                        Grid.Row="4" 
                                        Grid.Column="1" />
                        </Grid>
                        <Line X1="0" X2="440" Y1="0" Y2="0" Margin="0,15,0,15" StrokeThickness="1" Stroke="White"></Line>
                    </StackPanel>

                </DataTemplate>
            </ListBox.ItemTemplate>
        </ListBox>
    </Grid>
</Grid>
```

Los datos que se muestran en la consulta son cargados de la base de datos en el momento que accedemos a la página:

```
protected override void OnNavigatedTo(NavigationEventArgs e)
{
    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        var clients = from Client client in db.clients
                      select client;

        ObservableCollection<Client> items = new ObservableCollection<Client>();
        foreach (Client c in clients)
        {
            items.Add(c);
        }

        ClientItems = new ObservableCollection<Client>(items);
    }
}
```

Los elementos la interfaz están enlazados (Data binding) a los elementos de la colección _ClientItems_.

### Registro de pedidos

La siguiente imagen muestra la interfaz para el registro de pedidos:

![Consulta de clientes](/report-iii-wp8-web-services/ws_wp8_07.png)

El diseño correspondiente en XAML (archivo _View/ShopView.xaml_):

```
<!--LayoutRoot is the root grid where all page content is placed-->
<Grid x:Name="LayoutRoot" Background="Transparent">
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto" MinHeight="129"/>
        <RowDefinition/>
    </Grid.RowDefinitions>

    <!--TitlePanel contains the name of the application and page title-->
    <StackPanel Grid.Row="0" Margin="12,17,0,28">
        <TextBlock Text="Control de Requisiciones" Style="{StaticResource PhoneTextNormalStyle}"/>
        <TextBlock Text="Requisición" Margin="9,-7,0,0" Style="{StaticResource PhoneTextTitle1Style}" FontSize="48"/>
    </StackPanel>

    <!--ContentPanel - place additional content here-->
    <Grid x:Name="ContentPanel" Grid.Row="1" Margin="12,0,12,0">

        <Grid Width="440" Margin="8,0,8,570">
            <Grid.ColumnDefinitions>
                <ColumnDefinition Width="170" />
                <ColumnDefinition Width="*" />
            </Grid.ColumnDefinitions>
            <Grid.RowDefinitions>
                <RowDefinition Height="Auto" />
            </Grid.RowDefinitions>

            <TextBlock Grid.Row="0" Grid.Column="0"
                       FontSize="{StaticResource PhoneFontSizeLarge}"
                       VerticalAlignment="Center" Margin="0,15,25,14">
                ID Cliente:
            </TextBlock>
            <TextBox Grid.Row="0" Text="{Binding IdClient,Mode=TwoWay}" Margin="150,0,10,0" Grid.ColumnSpan="2" />
        </Grid>


        <ScrollViewer HorizontalAlignment="Left" Height="391" Margin="10,74,0,0" VerticalAlignment="Top" Width="436">
            <ListBox x:Name="detailList" ItemsSource="{Binding DetailItems}" Height="364" Width="421">
                <ListBox.ItemTemplate>
                    <DataTemplate>
                        <Grid Width="440">
                            <Grid.ColumnDefinitions>
                                <ColumnDefinition Width="100" />
                                <ColumnDefinition Width="*" />
                            </Grid.ColumnDefinitions>
                            <TextBox Text="{Binding Amount}" Grid.Column="0" IsReadOnly="True"/>
                            <TextBox Text="{Binding Item}" Grid.Column="1" IsReadOnly="True"/>
                        </Grid>
                    </DataTemplate>
                </ListBox.ItemTemplate>
            </ListBox>
        </ScrollViewer>

        <Grid Width="440" Margin="10,470,6,87">
            <Grid.ColumnDefinitions>
                <ColumnDefinition Width="290" />
                <ColumnDefinition Width="90" />
                <ColumnDefinition Width="*" />
            </Grid.ColumnDefinitions>
            <TextBox Text="{Binding NewItem,Mode=TwoWay}"
                     Grid.Column="0" 
                     Margin="0,0,10,0" />
            <TextBox Text="{Binding NewItemAmount,Mode=TwoWay}"
                     Grid.ColumnSpan="2" 
                     Margin="275,0,15,0" 
                     TextAlignment="Center" />
            <Button x:Name="addItemButton" Grid.Column="1" Click="addItemButton_Click" Grid.ColumnSpan="2" Margin="75,0,10,0">
                <Button.Background>
                    <ImageBrush Stretch="Uniform" ImageSource="/Images/AddNew.png"/>
                </Button.Background>
            </Button>
        </Grid>
        <Button x:Name="saveRequisitionButton" Content="Guardar pedido" HorizontalAlignment="Left" Margin="10,557,0,0" VerticalAlignment="Top" Width="446" Click="saveRequisitionButton_Click_1" />

    </Grid>
</Grid>
```

El código que se encarga de almacenar los pedidos es el siguiente:

```
private void saveRequisitionButton_Click_1(object sender, RoutedEventArgs e)
{
    if (DetailItems.Count == 0)
    {
        MessageBox.Show("La lista esta vacía.");
        return;
    }

    int id = 0;
    try
    {
        id = Int32.Parse(IdClient);
    }
    catch (FormatException fe)
    {
        MessageBox.Show("Verifica el ID del cliente.");
        return;
    }


    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        string date = DateTime.Now.Year + "-" + DateTime.Now.Month + "-" + DateTime.Now.Day;
        var keys = (from Key k in db.keys select k).First();
        int newRequestId = keys.NewIdRequest;
        int year = DateTime.Now.Year;
        int month = DateTime.Now.Month;
        int day = DateTime.Now.Day;
        int hour = DateTime.Now.Hour;
        int minute = DateTime.Now.Minute;
        int second = DateTime.Now.Second;
        Request request = new Request
        {
            IdRequest = newRequestId,
            IdClient = id,
            RequestDate = new DateTime(year, month, day, hour, minute, second)
        };

        keys.NewIdRequest += 1;
        db.requests.InsertOnSubmit(request);
        bool ok = true;
        try
        {
            db.SubmitChanges();
        }
        catch (Exception ex)
        {
            Debug.WriteLine("ERROR: " + ex.ToString());
            ok = false;
        }

        if (ok)
        {
            var result = from r in db.requests
                         select r;

            foreach (Detail detail in DetailItems)
            {
                db.details.InsertOnSubmit(new Detail
                {
                    IdDetail = keys.NewIdDetail,
                    IdRequest = newRequestId,
                    Item = detail.Item,
                    Amount = detail.Amount
                });

                keys.NewIdDetail += 1;
            }

            try
            {
                db.SubmitChanges();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("ERROR: " + ex.ToString());
                ok = false;
            }

            if (!ok)
            {
                MessageBox.Show("¡ERROR: No se pudo guardar el pedido!");
            }
        }
        else
        {
            MessageBox.Show("¡ERROR: No se pudo guardar el pedido!");
        }

        if (ok)
        {
            MessageBox.Show("La requisicón se ha guardado.");
            IdClient = String.Empty;
            DetailItems.Clear();
        }
    }
}
```

### Consulta de pedidos

La siguiente imagen muestra la interfaz para la consulta de pedidos:

![Consulta de pedidos](/report-iii-wp8-web-services/ws_wp8_08.png)

El diseño correspondiente en XAML (archivo _View/QueryShopView.xaml_):

```
<!--LayoutRoot is the root grid where all page content is placed-->
<Grid x:Name="LayoutRoot" Background="Transparent">
    <Grid.RowDefinitions>
        <RowDefinition Height="Auto"/>
        <RowDefinition Height="*"/>
    </Grid.RowDefinitions>

    <!--TitlePanel contains the name of the application and page title-->
    <StackPanel Grid.Row="0" Margin="12,17,0,28">
        <TextBlock Style="{StaticResource PhoneTextNormalStyle}">
            <Run Text="Control de Requisiciones"/>
            <LineBreak/>
            <Run Text=""/>
        </TextBlock>
        <TextBlock Text="Consulta pedidos" Margin="9,-7,0,0" Style="{StaticResource PhoneTextTitle1Style}" FontSize="48"/>
    </StackPanel>

    <!--ContentPanel - place additional content here-->
    <Grid x:Name="ContentPanel" Grid.Row="1" Margin="12,0,12,0">
        <ListBox x:Name="queryShopsList" ItemsSource="{Binding QueryRequestDetails}">
            <ListBox.ItemTemplate>
                <DataTemplate>
                    <StackPanel>
                        <Grid Width="440">
                            <Grid.ColumnDefinitions>
                                <ColumnDefinition Width="130" />
                                <ColumnDefinition Width="*" />
                            </Grid.ColumnDefinitions>
                            <Grid.RowDefinitions>
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                                <RowDefinition Height="Auto" />
                            </Grid.RowDefinitions>

                            <TextBlock Text="Id Pedido:"
                                   Grid.Row="0"
                                   Grid.Column="0"
                                   VerticalAlignment="Center"
                                   FontWeight="Bold"/>
                            <TextBlock Text="{Binding IdRequest,Mode=TwoWay}"
                                   Grid.Row="0"
                                   Grid.Column="1"/>

                            <TextBlock Text="Cliente:"
                                   Grid.Row="1"
                                   Grid.Column="0"
                                   VerticalAlignment="Center"
                                   FontWeight="Bold"/>
                            <TextBlock Text="{Binding ClientName,Mode=TwoWay}"
                                   Grid.Row="1"
                                   Grid.Column="1"/>

                            <TextBlock Text="Fecha:"
                                   Grid.Row="2"
                                   Grid.Column="0"
                                   VerticalAlignment="Center"
                                   FontWeight="Bold"/>
                            <TextBlock Text="{Binding Date,Mode=TwoWay}"
                                   Grid.Row="2"
                                   Grid.Column="1"/>

                            <ListBox ItemsSource="{Binding Items}"
                                     Grid.Row="3"
                                     Grid.Column="1">
                                <ListBox.ItemTemplate>
                                    <DataTemplate>
                                        <Grid Width="310">
                                            <Grid.ColumnDefinitions>
                                                <ColumnDefinition Width="80" />
                                                <ColumnDefinition Width="*" />
                                            </Grid.ColumnDefinitions>
                                            <Grid.RowDefinitions>
                                                <RowDefinition Height="Auto" />
                                            </Grid.RowDefinitions>

                                            <TextBlock Text="{Binding Amount,Mode=TwoWay}" 
                                                       Grid.Row="0"
                                                       Grid.Column="0"/>
                                            <TextBlock Text="{Binding Name,Mode=TwoWay}"
                                                       Grid.Row="0"
                                                       Grid.Column="1"/>
                                                       
                                        </Grid>
                                    </DataTemplate>
                                </ListBox.ItemTemplate>
                            </ListBox>
                        </Grid>

                        <Line X1="0" X2="440" Y1="0" Y2="0" Margin="0,15,0,15" StrokeThickness="1" Stroke="White"></Line>
                    </StackPanel>
                </DataTemplate>
            </ListBox.ItemTemplate>

        </ListBox>
    </Grid>
</Grid>
```

La lógica detras de esta operación se muestra en el siguiente listado:

```
protected override void OnNavigatedTo(NavigationEventArgs e)
{
    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        var requestList = from detail in db.details
                          select new
                          {
                              detail.Request.IdRequest,
                              detail.Request.Client.Name,
                              detail.Request.Client.MiddleName,
                              detail.Request.Client.LastName,
                              detail.Item,
                              detail.Amount,
                              detail.Request.RequestDate
                          };

        int size = requestList.Count();
        int i = 0;
        MyWebService.RequestDetail[] items = new MyWebService.RequestDetail[size];
        foreach (var request in requestList)
        {
            items[i] = new MyWebService.RequestDetail();
            items[i].IdRequest = request.IdRequest + "";
            items[i].FullName = request.Name + " " +
                                request.MiddleName + " " +
                                request.LastName;
            items[i].Item = request.Item;
            items[i].Amount = request.Amount + "";
            items[i].RequestDate = request.RequestDate.ToString();
            i++;
        }

        var requestDetails = processReports(items);
        QueryRequestDetails = new ObservableCollection<RequestReport>(requestDetails);
    }

    base.OnNavigatedTo(e);
}

private ObservableCollection<RequestReport> processReports(MyWebService.RequestDetail[] result)
{
    int prev = 0;
    ObservableCollection<RequestReport> reports = new ObservableCollection<RequestReport>();
    RequestReport report = new RequestReport();
    ObservableCollection<ItemDetail> details = new ObservableCollection<ItemDetail>();
    bool first = true;
    foreach (var row in result)
    {
        int id = Int32.Parse(row.IdRequest);
        if (id != prev)
        {
            if (!first) {
                report.Items = new ObservableCollection<ItemDetail>(details);
                details.Clear();
                reports.Add(report);
                report = new RequestReport();
            }

            first = false;
            prev = id;
            report.IdRequest = id + "";
            report.ClientName = row.FullName;
            report.Date = row.RequestDate;
            details.Add(new ItemDetail { Amount = row.Amount, Name = row.Item });
        }
        else
        {
            details.Add(new ItemDetail { Amount = row.Amount, Name = row.Item });
        }
    }

    if (details.Count > 0)
    {
        report.Items = new ObservableCollection<ItemDetail>(details);
        reports.Add(report);
    }

    return reports;
}
```

### La sincronización con el servidor

Esta operación consiste de varios métodos, en parte porque la comunicación con el Web service se realiza de manera asíncrona, vemos el código y después explicamos lo que sea necesario. 

En el constructor damos de alta los métodos que se encargarán de tratar con las respuestas del Web service.
```
private MyWebService.RequestPortTypeClient ws;
// Constructor
public MainPage()
{
    InitializeComponent();
    Loaded += MainPage_Loaded;
    ws = new MyWebService.RequestPortTypeClient();
    ws.GetAllClientsCompleted += ws_GetAllClientsCompleted;
    ws.GetAllRequestsCompleted += ws_GetAllRequestsCompleted;
    ws.GetAllDetailsCompleted += ws_GetAllDetailsCompleted;
    ws.SynchronizeCompleted += ws_SynchronizeCompleted;
}
```

Y ahora sí la sincronización: 

```
private void syncOperation_Click_1(object sender, EventArgs e)
{
    SetProgressIndicator(true);
    SystemTray.ProgressIndicator.Text = "Sincronizando datos con el servidor.";
    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        var C = from c in db.clients select c;
        var R = from r in db.requests select r;
        var D = from d in db.details select d;

        MyWebService.Client[] clients = new MyWebService.Client[C.Count()];
        MyWebService.Request[] requests = new MyWebService.Request[R.Count()];
        MyWebService.Detail[] details = new MyWebService.Detail[D.Count()];

        int i = 0;
        foreach (var c in C)
        {
            clients[i] = new MyWebService.Client();
            clients[i].IdClient = c.IdClient + "";
            clients[i].Name = c.Name;
            clients[i].MiddleName = c.MiddleName;
            clients[i].LastName = c.LastName;
            clients[i].Address = c.Address;
            i++;
        }

        i = 0;
        foreach (var r in R)
        {
            requests[i] = new MyWebService.Request();
            requests[i].IdRequest = r.IdRequest + "";
            requests[i].IdClient = r.IdClient + "";
            requests[i].RequestDate = MySqlDateFormat(r.RequestDate);
            i++;
        }

        i = 0;
        foreach (var d in D)
        {
            details[i] = new MyWebService.Detail();
            details[i].IdDetail = d.IdDetail + "";
            details[i].IdRequest = d.IdRequest + "";
            details[i].Item = d.Item;
            details[i].Amount = d.Amount + "";
            i++;
        }

        ws.SynchronizeAsync(clients, requests, details);
    }
}

void ws_SynchronizeCompleted(object sender, MyWebService.SynchronizeCompletedEventArgs e)
{
    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        if (db.DatabaseExists())
        {
            db.DeleteDatabase();
            db.CreateDatabase();
        }
    }

    ws.GetAllClientsAsync();
}

void ws_GetAllClientsCompleted(object sender, MyWebService.GetAllClientsCompletedEventArgs e)
{
    Collection<Client> newClients = new Collection<Client>();
    foreach (var row in e.Result)
    {
        Client c = new Client
        {
            IdClient = Int32.Parse(row.IdClient),
            Name = row.Name,
            MiddleName = row.MiddleName,
            LastName = row.LastName,
            Address = row.Address
        };

        newClients.Add(c);
    }


    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        db.clients.InsertAllOnSubmit(newClients);
        db.SubmitChanges();

        ws.GetAllRequestsAsync();
    }
}


void ws_GetAllRequestsCompleted(object sender, MyWebService.GetAllRequestsCompletedEventArgs e)
{
    Collection<Request> newRequests = new Collection<Request>();
    foreach (var row in e.Result)
    {
        Request r = new Request
        {
            IdRequest = Int32.Parse(row.IdRequest),
            IdClient = Int32.Parse(row.IdClient),
            RequestDate = SQLServerDateFormat(row.RequestDate)
        };
        newRequests.Add(r);
    }

    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        db.requests.InsertAllOnSubmit(newRequests);
        db.SubmitChanges();

        ws.GetAllDetailsAsync();
    }
}

private string MySqlDateFormat(DateTime dateTime)
{
    return dateTime.Year + "-"
            + dateTime.Month + "-"
            + dateTime.Day + " "
            + dateTime.Hour + ":"
            + dateTime.Minute + ":"
            + dateTime.Second;
}

private DateTime SQLServerDateFormat(string rd)
{
    string[] tokens = rd.Split(new char[] { '-', ' ', ':' });
    int year = Int32.Parse(tokens[0]);
    int month = Int32.Parse(tokens[1]);
    int day = Int32.Parse(tokens[2]);
    int hour = Int32.Parse(tokens[3]);
    int minute = Int32.Parse(tokens[4]);
    int second = Int32.Parse(tokens[5]);

    return new DateTime(year, month, day, hour, minute, second);
}

void ws_GetAllDetailsCompleted(object sender, MyWebService.GetAllDetailsCompletedEventArgs e)
{
    Collection<Detail> newDetails = new Collection<Detail>();
    foreach (var row in e.Result)
    {
        Detail d = new Detail
        {
            IdDetail = Int32.Parse(row.IdDetail),
            IdRequest = Int32.Parse(row.IdRequest),
            Item = row.Item,
            Amount = Int32.Parse(row.Amount)
        };
        newDetails.Add(d);
    }

    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        db.details.InsertAllOnSubmit(newDetails);
        db.SubmitChanges();

    }

    updateKeys(); // <-------------

    SetProgressIndicator(false); 
}
```

Nótese que casi al final de la sincronización se actualizan las claves primarias, el método `updateKeys()` es el siguiente:

```
private void updateKeys()
{
    int idClient = 1;
    int idRequest = 1;
    int idDetail = 1;
    string cs = RequisitionDataContext.DBConnectionString;
    using (RequisitionDataContext db = new RequisitionDataContext(cs))
    {
        if (db.clients.Count() > 0)
        {
            var id = db.clients.Max(x => x.IdClient);
            idClient = Math.Max(idClient, id + 1);
        }

        if (db.requests.Count() > 0)
        {
            var id = db.requests.Max(x => x.IdRequest);
            idRequest = Math.Max(idRequest, id + 1);
        }

        if (db.details.Count() > 0)
        {
            var id = db.details.Max(x => x.IdDetail);
            idDetail = Math.Max(idDetail, id + 1);
        }

        Key current = new Key();
        if (db.keys.Count() > 0)
        {
            current = (from Key k in db.keys select k).First();
        }

        current.NewIdClient = idClient;
        current.NewIdRequest = idRequest;
        current.NewIdDetail = idDetail;

        db.keys.InsertOnSubmit(current);
        db.SubmitChanges();
    }
}
```

Hasta aquí la explicación. Hay muchas cosas que no se abordaron aquí pero si las más importantes, en la siguiente sección se indica como obtener el código fuente para probar la aplicación.

## Código fuente

El código tanto del cliente como del servidor están disponibles en Bitbucket en las siguientes direcciones:

[https://bitbucket.org/rendon/request_ws](https://bitbucket.org/rendon/request_ws)
[https://bitbucket.org/rendon/requisition_wp8](https://bitbucket.org/rendon/requisition_wp8)

O bien pueden clonar los proyectos:
```
$ git clone https://rendon@bitbucket.org/rendon/request_ws.git
$ git clone https://rendon@bitbucket.org/rendon/requisition_wp8.git
```

La licencia del Web service es GPLv3.

La licencia de la aplicación cliente es GPLv3, con una posible excepción del código generado por Visual Studio para comunicarnos con el Web service, del cual desconozco que políticas se apliquen.

## Por hacer

Este trabajo no cumplió del todo con lo que el profesor solicito, en parte porque no entendí problema en su totalidad. En el siguiente reporte se explica cual fue el problema. 

Queda de tarea para el lector corregir el problema para que cumpla con lo que el profesor pidió, no es muy complicado. 

## Referencias

- [Creating Web Services with PHP and SOAP](http://www.sitepoint.com/web-services-with-php-and-soap-1/)
- [Documentaciónde NuSOAP](http://nusoap.sourceforge.net/)
- [Microsoft Developer Network](http://msdn.microsoft.com/en-US/)
