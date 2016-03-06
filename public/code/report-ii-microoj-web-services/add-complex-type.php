$server->wsdl->addComplexType('Problem', 'complexType', 'struct', 'all', '',
    array(
        'id' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1'),
        'title' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1'),
        'description' => array(
            'type' => 'xsd:string',
            'minOccurs' => '1',
            'maxOccurs' => '1')
        )
    );
