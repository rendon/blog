$server->wsdl->addComplexType(
    'ArrayOfProblem',
    'complexType',
    'array',
    'sequence',
    '',
    array(
        'problem' => array(
            'type'      => 'tns:Problem',
            'minOccurs' => '0', 
            'maxOccurs' => 'unbounded'
        )
    )
);
