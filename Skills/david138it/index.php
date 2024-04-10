<?php
$user = "YOUR-NAME";
$password = "YOUR-PASSWORD";
$database = "YOUR-DB";
$table1 = "experience";
$table2 = "results";
echo '
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0">
    <link rel="stylesheet" href="css/style.css">
    <title>david138it</title>
</head>
<body>
    <!--HEADER-->
    <header class="header fixed" id="header">
        <div class="container">
            <div class="header__nav">
                <p>mail - david138it@gmail.com</p>
                <p><a href="https://github.com/David138it">github</a></p>
                <p><a href="http://www.linkedin.com/in/david-gabuniya-3bb954237">linkedin</a></p>
                <p>telegram - @david138it</p>
                <p></p>
             </div>
        </div>
    </header>
    <!--SECTIONS-->
    <!--CARDS-->
    <section>
        <div class="container">
            <div class="cards">
                <div class="card__content" id="page__fixed">
                    <h2 class="card_hidden" onclick="card__hidden(this)">Engineer</h2>
                    <div style="text-align: left;">
                        <ul>
                            <li>
                                <strong>Давид Константинович:</strong> 31 год; Иркутск; 
                                <strong>Навыки:</strong> Html, Css, Timeweb, Linux, Qemu-kvm, Lamp, Mysql, Postgresql, Windows, Powershell, Rinex, Одночастотные приемники СРНС, C++, Virtualbox, DHCP-протокол, DNS, Ssh, Iptables, Nmap, Tcpdump, Ftp, Squid, Rkhunter, Crontab, Python, Wordpress, Bash, Hyper-v, Pxe, Kickstart, Firebird, Pgadmin4, Etl-процессы, Ddl, Dwh, AntiFraud, Yandex Cloud CLI, Nginx, Clickhouse, Git, Hadoop, Docker, Cloud Functions, API Gateway, Ipsec, Certificate Manager;
                                <strong>Feedback:</strong> david138it@gmail.com; telegram - @david138it; http://www.linkedin.com/in/david-gabuniya-3bb954237; https://github.com/David138it;
                            </li>
                            <li>
                                <strong>О себе:</strong> Уверенно администрирую в Linux и Windows системах; Могу развернуть веб-сервер Lamp, виртуальные машины в Qemu-kvm, Virtualbox, Hyper-V и сервисы в timeweb.clouds, yandex.clouds; Работаю с базами данных и умею писать SQL-запросы; Работаю с огромными массивами данных - собирать, обрабатывать и хранить их правильным образом; Программирую на C++ и Python; Понимаю работу TCP/IP, умею диагностировать и решать проблемы безопасности сети различным утилитами; Могу создать отказоустойчивые облачные системы, работать с управляемыми базами данных и контейнерами; Знаю основы бессерверных технологий и подходы к созданию защищённой от внешних атак облачной инфраструктуры; свободно читаю и перевожу техническую документацию на английском языке; Умею работать в команде и действовать самостоятельно; Есть желание активно развиваться, изучать новые технологии и инструменты; Не меньше двух лет работал на аналогичной позиции;</li>
                            </li>
                            <li>
                                <strong>Услуги:</strong>
                                <ul>
                                    <li>Установка и администрирование ОС Linux и Windows;</li>
                                    <li>Установка и администрирование веб-сервера Lamp;</li>
                                    <li>Установка и администрирование виртуальных машин в Qemu-kvm, Virtualbox и Hyper-v;</li>
                                    <li>Установка и администрирование облачных серверов Yandex.Clouds и Timeweb.Clouds;</li>
                                    <li>Установка, администрирование и написание Sql-запросов баз данных на Mysql и Postgresql;</li>
                                    <li>Верстка сайтов;</li>
                                    <li>Обработка и сортировка данных на C++ и Python;</li>
                                    <li>Восстановление работоспособности ПК, периферийных устройств, оборудования видеоконференцсвязи, аудио-видеофиксации, локальной сети при сбоях или выходе из строя сетевого оборудования;</li>
                                    <li>Установка, обновление и контроль состояния программного обеспечения на объектах автоматизации;</li>
                                    <li>Техническая поддержка пользователей;</li>
                                    <li>Разработка решений, которые упростят эксплуатацию и автоматизируют рутину;</li>
                                    <li>Обеспечение бесперебойной работы сервисов и улучшение их производительности;</li>
                                    <li>Разработка корпоративных хранилищ архивных данных;</li>
                                    <li>Разработка эффективных правил автоматизированной обработки, которые требуют меньше ресурсов и снижают потери и сбои;</li>
                                    <li>Сформировать условия для сбора информации, которая должна попасть на обработку и последующее хранение;</li>
                                    <li>Настройка и автоматизация процессов сбора, трансформации, очистки, хранения и первичного анализа данных с помощью SQL и базового Python на примерах реальных задач</li>
                                    <li>Управление облачной инфраструктурой</li>
                                    <li>Хранение и анализ данных</li>
                                    <li>Работа с контейнерами</li>
                                    <li>Разработка приложений в облаке</li>
                                    <li>Защита облачных ресурсов</li>
                                    <!--
                                    <li>разработать программу, которая переводит текст с английского языка на русский, или наоборот;</li>                
                                    -->
                                </ul>     
                            </li>
                        </ul>
                    </div>
                </div>
                <div class="card__content" id="">
                    <h2 class="card_hidden" onclick="card__hidden(this)">Опыт работы</h2>
                    <div style="text-align: left;">
                        <ul>            
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
        <li><strong>
        ' . $row['begin'] . ' -
        ' . $row['finish'] . ':</strong>
        ' . $row['place'] . ';
        ' . $row['specialization'] . '; <strong>Дополнительная информация:</strong>
        ' . $row['content'] . '; <strong>Достижения:</strong>
        ' . $row['progress'] . ';
        </li>
        ';
    }
} catch (PDOException $e) {
    print "Error!: " . $e->getMessage() . "<br/>";
    die();
}
echo '
                        </ul>
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
