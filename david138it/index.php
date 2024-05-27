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
                    <h2 class="card_hidden" onclick="card__hidden(this)">Engineer</h2>
                    <div style="text-align: left;">
                        <p>
                            <strong>О себе:</strong> Давид, Инженер-программист, г. Иркутск. Я специалист в области информационных технологий. У меня более 5 лет опыта в администрировании серверов различных ОС и в разработки скриптов, ПО и БД. В текущем месте работы внедряю специализированные программные обеспечения, ввожу в эксплуатацию технику - принтеры, сканеры, компьютеры и администрирую сервера и виртуальные машины на windows. Для саморазвития я в свободное время читаю и перевожу техническую документацию на английском языке, программирую на Python и C++, администрирую свой веб-сервер и разрабатываю сайт-портфолио. Имеются свои проекты в github https://github.com/dato38it/. Мне интересно работать в команде, активно развиваться в программировании и изучать новые технологии.<br>
                            <strong>Навыки:</strong> Виртуализация, Linux, Html, Css, Sql, Clouds, Windows, C++, Bash, Python, English, Docker.<br>
                            <strong>Обратная связь:</strong> dato38it@yandex.ru, telegram - @dato38it.<br>
                            <strong>Услуги:</strong><ul>
                                <li>Верстка Веб-страниц по макету.</li>
                                <li>Администрирование виртуальных и локальных серверов, Веб-серверов Lamp и Django, Баз данных, Облачных сервисов.</li>
                                <li>Написание Sql запросов в базе данных и скриптов для администрирования серверов и автоматизации рутиной работы.</li>
                                <li>Перенос данных с сервера или с базы данных.</li>
                                <li>Разработка Веб-сайта, Баз данных, Telegram бота.</li> 
                                <li>Обработка и сортировка данных на Python и Sql-запросах.</li>
                            </ul><br>
                        </p>
                    </div>
                </div>
                <div class="card__content" id="">
                    <h2 class="card_hidden" onclick="card__hidden(this)">Опыт работы</h2>
                    <div style="text-align: left;">
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
