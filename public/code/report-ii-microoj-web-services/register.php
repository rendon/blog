$server->register('Judge.create_problem',
    array(
        'user' => 'xsd:string',
        'password' => 'xsd:string',
        'title' => 'xsd:string',
        'description' => 'xsd:string',
        'author' => 'xsd:integer'),
    array('return' => 'xsd:integer'),
    'http://localhost/microoj_ws/judge.php'
);
