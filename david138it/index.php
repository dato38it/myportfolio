<?php
$user = "tuser";
$password = "tpassword";
$database = "thost";
$table1 = "experience";
$table2 = "results";
echo '
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0">
    <link rel="stylesheet" href="css/style.css">
    <title>thost</title>
</head>
<body>
    <!--SECTIONS-->
    <!--CARDS-->
    <section>
        <div class="container">
            <div class="cards">
                <div class="card__content" id="page__fixed">
                    <h2 class="card_hidden" id="aboutMe" onclick="card__hidden(this)">Обо мне</h2>
                    <div style="display:none; text-align:left; &{head};">
                        <p>
                            <strong>Инженер-программист:</strong> г. Иркутск. Я специалист в области информационных технологий. У меня более 5 лет опыта в администрировании серверов различных ОС и в разработки скриптов, ПО и БД. В текущем месте работы внедряю специализированные программные обеспечения, ввожу в эксплуатацию технику - принтеры, сканеры, компьютеры и администрирую сервера и виртуальные машины на windows. Для саморазвития я в свободное время читаю и перевожу техническую документацию на английском языке, программирую на Python и C++, администрирую свой веб-сервер и разрабатываю сайт-портфолио. Имеются свои проекты в github https://github.com/it38dato. Мне интересно работать в команде, активно развиваться в программировании и изучать новые технологии.<br>
                            <strong>Навыки:</strong> Html, Css, Windows, Виртуализация, Linux, Sql, Bash, Clouds, Python, English, Etl-процессы, Dwh, AntiFraud, Спутниковые радионавигационные системы, С++.<br>
                            <strong>Обратная связь:</strong> it38dato@gmail.com, telegram - @it38dato.<br>
                            <strong>Услуги:</strong><br>
                            # Верстка Веб-страниц по макетам.<br>
                            # Администрирование локальных, виртуальных и облачных серверов.<br>
                            # Администрирование Веб-сервера Lamp.<br>
                            # Администрирование Веб-сервера Django.<br>
                            # Администрирование Веб-сервера React.js.<br>
                            # Администрирование базы данных.<br>
                            # Разработка Веб-сайта Django.<br>
                            # Разработка Веб-сайта React.js.<br>
                            # Разработка Телеграм бота Переводчик.<br>
                            # Разработка базы данных.<br>
                            # Разработка Хранилище данных.<br>
                            # Написание Sql запросов.<br>
                            # Обработка и сортировка данных на Python, C++ и Sql-запросах.<br>
                            # Анализ сетевых технологий.
                        </p>
                    </div>
                </div>
                <div class="card__content" id="experience" style="text-align: left;">  
                    <p>Опыт работы / Образование</p>                  
                    <p class="card_hidden" onclick="card__hidden(this)">Show</p>
                    <div style="display:none;" style=&{head};>
                        <p>            
';
try {
    $db = new PDO("mysql:host=localhost;dbname=$database", $user, $password);
    $query = $db->query("
        select * from $database.$table2 
        inner join $database.$table1 
        on $table1.experience_id=$table2.experienceId
        order by $table1.begin;
    ");
    foreach($query as $row) {
        echo '
        <strong>
        ' . $row['begin'] . ' -
        ' . $row['finish'] . ', </strong>
        ' . $row['place'] . ',
        ' . $row['specialization'] . '<br><strong>Дополнительная информация.</strong>
        ' . $row['content'] . '<br><strong>Достижения.</strong>
        ' . $row['progress'] . '<br>
        <br>
        ';
    }
} catch (PDOException $e) {
    print "Error!: " . $e->getMessage() . "<br/>";
    die();
}
echo '
                        </p>
                    </div>
                </div>
            </div>  
        </div>
    </section> 
    <!-- JS -->
    <script src="js/jquery.js"></script>
    <script src="js/main.js"></script>
</body>
</html>
'
?>