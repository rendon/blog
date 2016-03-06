MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *testButton = new QPushButton("Test service");
    connect(testButton, SIGNAL(clicked()), this, SLOT(testService()));
    layout->addWidget(testButton);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testService()
{
    QString message("<soapenv:Envelope xmlns:soapenv='http://schemas.xmlsoap.org/soap/envelope/' xmlns:mys='MyService'> <soapenv:Header/> <soapenv:Body> <mys:Hello> <name>Rafael</name> </mys:Hello> </soapenv:Body> </soapenv:Envelope>");

    QUrl url("http://localhost/ws/index.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    QNetworkAccessManager *nm = new QNetworkAccessManager(this);
    QObject::connect(nm, SIGNAL(finished(QNetworkReply *)), this, SLOT(testFinished(QNetworkReply*)));
    nm->post(request, message.toAscii());
}

void MainWindow::testFinished(QNetworkReply *reply)
{
    QByteArray ans = reply->readAll();
    QString response(ans.data());

    // Process your response message
    qDebug() << response << endl;
}
