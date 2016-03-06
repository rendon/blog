function create_problem($user, $password, $title, $description, $author)
{
    if ($this->authenticate_user($user, $password) != VALID_USER) {
        return INVALID_USER;
    }

    $mysqli = $this->open_db();
    $query = $this->fips($title,
                         $description,
                         $author);

    $mysqli->query("SET NAMES UTF8");
    $mysqli->query($query);
    $code = $mysqli->insert_id;

    if ($code == 0) {
        if ($mysqli->errno == ER_DUP_ENTRY) {
            return ER_TITLE_ALREADY_TAKEN;
        } else {
            return ER_FAILED_TO_INSERT_RECORD;
        }
    }

    $mysqli->close();
    return $code;
}
