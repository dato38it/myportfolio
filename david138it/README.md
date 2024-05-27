# Веб-сайт с базой данных "Портфолио" для размещения своих достижений.
<ul>
    <li>
        установил и настроил виртуальную машину в Linux системе,
    </li>
    <li>
        установил и настроил тестовый веб-сервер Lamp в виртуальной машине,
    </li>
    <li>
        сверстал Html-страницу,
    </li>
    <li>
        разработал базу с таблицами в веб-сервере,
    </li>
    <li>
        подключил и настроил облачную виртуальную машину с аналогичной Linux системой,
    </li>
    <li>
        установил и настроил веб-сервер Lamp в облачной сервисе,&nbsp;
    </li>
    <li>
        произвел эспорт и импорт базы данных из тестовой в облачный сервис,&nbsp;
    </li>
    <li>
        зарегистрировал домен,&nbsp;
    </li>
    <li>
        в облачном сервисе вносил свои достижения.
    </li>
</ul>
<p>
    <strong>Task:</strong><br>
    Создание HTML-списков&nbsp;<br>
    <strong>Decision:</strong><br>
    &lt;ul&gt;<br>
    &lt;li&gt;Linux Server Administration&lt;/li&gt;<br>
    &lt;li&gt;Working with websites&lt;/li&gt;<br>
    &lt;/ul&gt;<br>
    <strong>Source:</strong><br>
    https://html5book.ru/html-lists/?ysclid=lis7im73ng615064864<br>
    <strong>Task:</strong><br>
    Установка Lamp<br>
    <strong>Decision:</strong><br>
    $ sudo apt update<br>
    $ sudo apt install apache2<br>
    $ sudo ufw app list<br>
    Available applications:<br>
    Apache<br>
    Apache Full<br>
    Apache Secure<br>
    OpenSSH<br>
    $ sudo ufw status<br>
    Status: inactive<br>
    $ google-chrome http://tip:80/<br>
    $ sudo ufw enable<br>
    $ sudo ufw allow in "Apache"<br>
    $ sudo ufw allow in "OpenSSH"<br>
    $ sudo ufw status<br>
    Status: active<br>
    To&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Action&nbsp;&nbsp; From<br>
    --&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ------&nbsp;&nbsp; ----<br>
    Apache&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ALLOW&nbsp;&nbsp; Anywhere&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
    OpenSSH&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ALLOW&nbsp;&nbsp; Anywhere&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
    Apache (v6)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ALLOW&nbsp;&nbsp; Anywhere (v6)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
    OpenSSH (v6)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ALLOW&nbsp;&nbsp; Anywhere (v6)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
    $ sudo ufw app list<br>
    Available applications:<br>
    Apache<br>
    Apache Full<br>
    Apache Secure<br>
    OpenSSH&nbsp;<br>
    $ sudo apt install mysql-server<br>
    $ sudo mysql<br>
    mysql&gt; ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'tpassword';<br>
    mysql&gt; exit<br>
    $ sudo mysql_secure_installation<br>
    ...<br>
    Press y|Y for Yes, any other key for No: y<br>
    ...<br>
    Please enter 0 = LOW, 1 = MEDIUM and 2 = STRONG: 1<br>
    ...<br>
    Change the password for root ? ((Press y|Y for Yes, any other key for No) : n<br>
    ...<br>
    Remove anonymous users? (Press y|Y for Yes, any other key for No) : y<br>
    ...<br>
    Disallow root login remotely? (Press y|Y for Yes, any other key for No) : n<br>
    ...<br>
    Remove test database and access to it? (Press y|Y for Yes, any other key for No) : y<br>
    ...<br>
    Reload privilege tables now? (Press y|Y for Yes, any other key for No) : y<br>
    ...<br>
    $ sudo mysql -u root -p<br>
    mysql&gt; SELECT user,authentication_string,plugin,host FROM mysql.user;<br>
    mysql&gt; rename user 'root'@'localhost' to 'tuser'@'localhost';<br>
    mysql&gt; create database tbase;<br>
    mysql&gt; show databases;<br>
    +--------------------+<br>
    | Database&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    +--------------------+<br>
    | tbase&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    ...<br>
    +--------------------+<br>
    mysql&gt; exit<br>
    $ sudo apt install php libapache2-mod-php php-mysql<br>
    $ php -v<br>
    $ sudo vim /etc/php/8.1/apache2/php.ini<br>
    $ cat /etc/php/8.1/apache2/php.ini | grep upload_max_filesize<br>
    upload_max_filesize = 32M<br>
    ...<br>
    post_max_size = 48M<br>
    ...<br>
    memory_limit = 256M<br>
    ...<br>
    max_execution_time = 600<br>
    ...<br>
    max_input_vars = 3000<br>
    ...<br>
    max_input_time = 1000<br>
    $ sudo service apache2 restart<br>
    $ sudo mkdir /var/www/thost<br>
    $ sudo chown -R $USER:$USER /var/www/thost<br>
    $ sudo vim /etc/apache2/sites-available/thost.conf<br>
    $ cat /etc/apache2/sites-available/thost.conf<br>
    &lt;VirtualHost *:80&gt;<br>
    &nbsp;&nbsp;ServerName thost<br>
    &nbsp;&nbsp;ServerAlias www.thost<br>
    &nbsp;&nbsp;ServerAdmin webmaster@localhost<br>
    &nbsp;&nbsp;DocumentRoot /var/www/thost<br>
    &nbsp;&nbsp;ErrorLog ${APACHE_LOG_DIR}/error.log<br>
    &nbsp;&nbsp;CustomLog ${APACHE_LOG_DIR}/access.log combined<br>
    &lt;/VirtualHost&gt;<br>
    $ sudo a2ensite thost<br>
    $ sudo a2dissite 000-default<br>
    $ sudo apache2ctl configtest<br>
    $ sudo systemctl reload apache2<br>
    $ vim /var/www/thost/index.html<br>
    $ cat /var/www/thost/index.html<br>
    &lt;html&gt;<br>
    &lt;head&gt;<br>
    &nbsp;&nbsp;&lt;title&gt;thost website&lt;/title&gt;<br>
    &lt;/head&gt;<br>
    &lt;body&gt;<br>
    &nbsp;&nbsp;&lt;h1&gt;Hello World!&lt;/h1&gt;<br>
    &nbsp;&nbsp;&lt;p&gt;This is the landing page of &lt;strong&gt;thost&lt;/strong&gt;.&lt;/p&gt;<br>
    &lt;/body&gt;<br>
    &lt;/html&gt;<br>
    $ google-chrome http://tip:80/<br>
    $ cat /etc/apache2/mods-enabled/dir.conf<br>
    &lt;IfModule mod_dir.c&gt;<br>
    &nbsp;&nbsp;DirectoryIndex index.html index.cgi index.pl index.php index.xhtml index.htm<br>
    &lt;/IfModule&gt;<br>
    # vim: syntax=apache ts=4 sw=4 sts=4 sr noet<br>
    $ sudo systemctl reload apache2<br>
    $ vim /var/www/thost/info.php<br>
    $ cat /var/www/thost/info.php<br>
    &lt;?php<br>
    phpinfo();<br>
    $ google-chrome http://tip:80/info.php<br>
    $ vim /var/www/thost/index.php<br>
    $ cat /var/www/thost/index.php<br>
    &lt;?php<br>
    $user = "tuser";<br>
    $password = "tpassword";<br>
    $database = "tbase";<br>
    $table1 = "ttable1";<br>
    $table2 = "ttable2";<br>
    try {<br>
    &nbsp;&nbsp;$db = new PDO("mysql:host=localhost;dbname=$database", $user, $password);<br>
    &nbsp;&nbsp;$query = $db-&gt;query("<br>
    &nbsp;&nbsp;&nbsp;&nbsp;select * from $database.$table2<br>
    &nbsp;&nbsp;&nbsp;&nbsp;inner join $database.$table1<br>
    &nbsp;&nbsp;&nbsp;&nbsp;on $table1.experience_id=$table2.experienceId;<br>
    &nbsp;&nbsp;");<br>
    &nbsp;&nbsp;foreach($query as $row) {<br>
    &nbsp;&nbsp;&nbsp;&nbsp;echo '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&lt;li&gt;&lt;strong&gt;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column1'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;-<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column2'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;:&lt;/strong&gt;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column3'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column4'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column5'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;' . $row['column6'] . '<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&lt;/li&gt;<br>
    &nbsp;&nbsp;&nbsp;&nbsp;';<br>
    &nbsp;&nbsp;}<br>
    } catch (PDOException $e) {<br>
    &nbsp;&nbsp;print "Error!: " . $e-&gt;getMessage() . "&lt;br/&gt;";<br>
    &nbsp;&nbsp;die();<br>
    }<br>
    $ google-chrome http://tip/index.php<br>
    <strong>Task:</strong><br>
    Создать базу и таблицы<br>
    <strong>Decision:</strong><br>
    $ sudo mysql -u root -p<br>
    mysql&gt; create database tbase;<br>
    mysql&gt; CREATE USER 'tuser'@'%' IDENTIFIED BY 'tpassword';<br>
    mysql&gt; GRANT ALL ON tbase.* TO 'tuser'@'%';<br>
    mysql&gt; exit<br>
    $ mysql -u tuser -p<br>
    mysql&gt; show databases;<br>
    +--------------------+<br>
    | Database&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    +--------------------+<br>
    | information_schema |<br>
    | performance_schema |<br>
    | tbase&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    +--------------------+<br>
    3 rows in set (0.07 sec)<br>
    mysql&gt; create table tbase.ttable1<br>
    &nbsp;&nbsp;(ttable1_id INT PRIMARY KEY AUTO_INCREMENT,<br>
    &nbsp;&nbsp;content VARCHAR(255));<br>
    CREATE TABLE tbase.ttable1<br>
    &nbsp;&nbsp;(ttable1_id INT PRIMARY KEY AUTO_INCREMENT,<br>
    &nbsp;&nbsp;column1 VARCHAR(255),<br>
    &nbsp;&nbsp;column2 VARCHAR(255),<br>
    &nbsp;&nbsp;column3 VARCHAR(255),<br>
    &nbsp;&nbsp;column4 VARCHAR(255),<br>
    &nbsp;&nbsp;column5 Date,<br>
    &nbsp;&nbsp;column6 Date);<br>
    mysql&gt; INSERT INTO tbase.ttable1<br>
    &nbsp;&nbsp;(column1, column2)<br>
    VALUES<br>
    &nbsp;&nbsp;("text1","text2"),<br>
    &nbsp;&nbsp;("text3","text4"),<br>
    &nbsp;&nbsp;("text5","text6"),<br>
    &nbsp;&nbsp;("text7","text8");<br>
    mysql&gt; select * from tbase.ttable1;<br>
    +------------+---------+---------+---------+---------+---------+---------+<br>
    | ttable1_id | column1 | column2 | column3 | column4 | column5 | column6 |<br>
    +------------+---------+---------+---------+---------+---------+---------+<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 1 | text1 | text2 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 2 | text3 | text4 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 3 | text5 | text6 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 4 | text7 | text8 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    +------------+---------+---------+---------+---------+---------+---------+<br>
    4 rows in set (0.00 sec)<br>
    mysql&gt; CREATE TABLE tbase.ttable2<br>
    &nbsp;&nbsp;(ttable2_id INT PRIMARY KEY AUTO_INCREMENT,<br>
    &nbsp;&nbsp;columnId INT,<br>
    &nbsp;&nbsp;column1 VARCHAR(500),<br>
    &nbsp;&nbsp;FOREIGN KEY (columnId) REFERENCES tbase.ttable1 (ttable1_id));<br>
    mysql&gt; INSERT INTO tbase.ttable2<br>
    &nbsp;&nbsp;(columnId, column1)<br>
    VALUES<br>
    &nbsp;&nbsp;(1, "text9"),<br>
    &nbsp;&nbsp;(1, "text10"),<br>
    &nbsp;&nbsp;(2, "text11"),<br>
    &nbsp;&nbsp;(3, "text12"),<br>
    &nbsp;&nbsp;(4, "text13");<br>
    mysql&gt; select * from tbase.ttable2;<br>
    +------------+----------+---------+<br>
    | ttable2_id | columnId | column1 |<br>
    +------------+----------+---------+<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 1 |&nbsp;&nbsp;&nbsp;&nbsp;1 | text9 |<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 2 |&nbsp;&nbsp;&nbsp;&nbsp;1 | text10 |<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 3 |&nbsp;&nbsp;&nbsp;&nbsp;2 | text11 |<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 4 |&nbsp;&nbsp;&nbsp;&nbsp;3 | text12 |<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 5 |&nbsp;&nbsp;&nbsp;&nbsp;4 | text13 |<br>
    +------------+----------+---------+<br>
    5 rows in set (0.00 sec)<br>
    mysql&gt; select * from tbase.ttable2<br>
    &nbsp;&nbsp;inner join tbase.ttable1<br>
    &nbsp;&nbsp;on ttable1.ttable1_id = ttable2.columnId;<br>
    +------------+----------+---------+------------+---------+---------+---------+---------+---------+---------+<br>
    | ttable2_id | columnId | column1 | ttable1_id | column1 | column2 | column3 | column4 | column5 | column6 |<br>
    +------------+----------+---------+------------+---------+---------+---------+---------+---------+---------+<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 1 |&nbsp;&nbsp;&nbsp;&nbsp;1 | text9 |&nbsp;&nbsp;&nbsp;&nbsp; 1 | text1 | text2 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 2 |&nbsp;&nbsp;&nbsp;&nbsp;1 | text10 |&nbsp;&nbsp;&nbsp;&nbsp; 1 | text1 | text2 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 3 |&nbsp;&nbsp;&nbsp;&nbsp;2 | text11 |&nbsp;&nbsp;&nbsp;&nbsp; 2 | text3 | text4 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 4 |&nbsp;&nbsp;&nbsp;&nbsp;3 | text12 |&nbsp;&nbsp;&nbsp;&nbsp; 3 | text5 | text6 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    |&nbsp;&nbsp;&nbsp;&nbsp; 5 |&nbsp;&nbsp;&nbsp;&nbsp;4 | text13 |&nbsp;&nbsp;&nbsp;&nbsp; 4 | text7 | text8 | NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;| NULL&nbsp;&nbsp;|<br>
    +------------+----------+---------+------------+---------+---------+---------+---------+---------+---------+<br>
    5 rows in set (0.00 sec)<br>
    mysql&gt; exit<br>
    <strong>Source:</strong><br>
    <a href="https://metanit.com/sql/mysql/2.5.php">https://metanit.com/sql/mysql/2.5.php</a><br>
    <a href="https://metanit.com/sql/mysql/5.2.php">https://metanit.com/sql/mysql/5.2.php</a><br>
    $ sudo apt install phpmyadmin php-mbstring php-zip php-gd php-json php-curl<br>
    ...<br>
    Configure database for phpmyadmin with dbconfig-common? [yes/no] y<br>
    ...<br>
    granting access to database phpmyadmin for phpmyadmin@localhost: failed.<br>
    error encountered creating user:<br>
    mysql said: ERROR 1819 (HY000) at line 1: Your password does not satisfy the current policy requirements<br>
    An error occurred while installing the database:<br>
    mysql said: ERROR 1819 (HY000) at line 1: Your password does not satisfy the current policy requirements . Your options are:<br>
    * abort - Causes the operation to fail; you will need to downgrade,<br>
    reinstall, reconfigure this package, or otherwise manually intervene<br>
    to continue using it. This will usually also impact your ability to<br>
    install other packages until the installation failure is resolved.<br>
    * retry - Prompts once more with all the configuration questions<br>
    ...<br>
    1. abort 2. retry 3. retry (skip questions) 4. ignore<br>
    Next step for database installation: 1<br>
    ...<br>
    Errors were encountered while processing:<br>
    phpmyadmin<br>
    needrestart is being skipped since dpkg has failed<br>
    E: Sub-process /usr/bin/dpkg returned an error code (1)<br>
    $ mysql -u tuser -p<br>
    mysql&gt; UNINSTALL COMPONENT "file://component_validate_password";<br>
    mysql&gt; exit<br>
    $ sudo apt install phpmyadmin<br>
    $ sudo apt install php8.1-fpm php8.1 libapache2-mod-php8.1 php8.1-common php8.1-mysql php8.1-xml php8.1-xmlrpc php8.1-imagick php8.1-cli php8.1-imap php8.1-opcache php8.1-soap php8.1-intl php8.1-bcmath unzip<br>
    $ mysql -u tuser -p<br>
    mysql&gt; INSTALL COMPONENT "file://component_validate_password";<br>
    mysql&gt; exit<br>
    $ sudo phpenmod mbstring<br>
    $ sudo systemctl restart apache2<br>
    $ sudo cp /etc/phpmyadmin/apache.conf /etc/apache2/conf-available/phpmyadmin.conf<br>
    $ sudo a2enconf phpmyadmin.conf<br>
    $ systemctl reload apache2<br>
    $ google-chrome http://tip/phpmyadmin<br>
    <strong>Source:</strong><br>
    https://bozza.ru/art-260.html<br>
    https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-22-04<br>
    https://losst.pro/ustanovka-chrome-v-ubuntu-18-04?ysclid=lmdflkvc3v463974954<br>
    https://qna.habr.com/q/439469?ysclid=lmdgkb49q827401606<br>
    https://steptuser.org/course/63054/syllabus<br>
    https://metanit.com/sql/mysql/2.5.php<br>
    https://metanit.com/sql/mysql/5.2.php<br>
    https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-20-04<br>
    https://serverspace.ru/support/help/osnovnye-komandy-ufw/<br>
    https://www.tutsmake.com/how-to-install-lamp-apache-mysql-php-in-ubuntu-22-04/<br>
    https://www.php.net/manual/ru/faq.html.php<br>
    https://www.8host.com/blog/kak-rabotayut-stroki-v-php/<br>
    https://www.youtube.com/watch?v=FxwPQkP3OGY&amp;t=611s<br>
    https://timeweb.com/ru/community/articles/kak-ustanovit-stek-lamp-na-ubuntu-20-04<br>
    https://wiki.merionet.ru/articles/perenos-bazy-dannyx-mysql-so-starogo-na-novyj-server<br>
    <strong>Task:</strong><br>
    Миграция баз данных<br>
    <strong>Decision:</strong><br>
    $ mysql -V<br>
    mysql Ver 8.0.34-0ubuntu0.22.04.1 for Linux on x86_64 ((Ubuntu))<br>
    $ sudo mysql -u root<br>
    mysql&gt; SELECT User, Host FROM mysql.user;<br>
    &nbsp;&nbsp;+------------------+-----------+<br>
    &nbsp;&nbsp;| User&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Host&nbsp;&nbsp; |<br>
    &nbsp;&nbsp;+------------------+-----------+<br>
    &nbsp;&nbsp;| root&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | localhost |<br>
    &nbsp;&nbsp;| tuser&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| localhost |<br>
    +------------------+-----------+<br>
    &nbsp;&nbsp;6 rows in set (0.43 sec)<br>
    mysql&gt; SHOW DATABASES;<br>
    &nbsp;&nbsp;+--------------------+<br>
    &nbsp;&nbsp;| Database&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    &nbsp;&nbsp;+--------------------+<br>
    &nbsp;&nbsp;| thost&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br>
    &nbsp;&nbsp;+--------------------+<br>
    &nbsp;&nbsp;6 rows in set (0.80 sec)<br>
    mysql&gt; exit<br>
    $ mysqldump -u root -p --opt thost &gt; thost.sql<br>
    $ ls thost.sql<br>
    thost.sql<br>
    $ scp -r /var/www/thost/* tuser@tip:/var/www/thost/<br>
    $ ssh -X tuser@tip<br>
    $ mysql -V<br>
    mysql Ver 8.0.34-0ubuntu0.22.04.1 for Linux on x86_64 ((Ubuntu))<br>
    $ mysql -u root -p<br>
    mysql&gt; create database thost;<br>
    mysql&gt; \q<br>
    $ mysql -u root -p thost &lt; thost.sql<br>
    $ mysql -u tuser -p<br>
    mysql&gt; show databases;<br>
    +--------------------+<br>
    | Database&nbsp;&nbsp;&nbsp;&nbsp; |<br>
    +--------------------+<br>
    | thost&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|<br>
    | information_schema |<br>
    | performance_schema |<br>
    +--------------------+<br>
    mysql&gt; USE thost;<br>
    <strong>Source:</strong><br>
    <a href="https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-22-04">https://www.digitalocean.com/community/tutorials/how-to-install-linux-apache-mysql-php-lamp-stack-on-ubuntu-22-04</a><br>
    <a href="https://losst.pro/ustanovka-chrome-v-ubuntu-18-04?ysclid=lmdflkvc3v463974954">https://losst.pro/ustanovka-chrome-v-ubuntu-18-04?ysclid=lmdflkvc3v463974954</a><br>
    <a href="https://qna.habr.com/q/439469?ysclid=lmdgkb49q827401606">https://qna.habr.com/q/439469?ysclid=lmdgkb49q827401606</a><br>
    <a href="https://steptuser.org/course/63054/syllabus">https://steptuser.org/course/63054/syllabus</a><br>
    <a href="https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-20-04">https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-20-04</a><br>
    <a href="https://www.tutsmake.com/how-to-install-lamp-apache-mysql-php-in-ubuntu-22-04/">https://www.tutsmake.com/how-to-install-lamp-apache-mysql-php-in-ubuntu-22-04/</a><br>
    <a href="https://www.php.net/manual/ru/faq.html.php">https://www.php.net/manual/ru/faq.html.php</a><br>
    <a href="https://www.8host.com/blog/kak-rabotayut-stroki-v-php/">https://www.8host.com/blog/kak-rabotayut-stroki-v-php/</a><br>
    <a href="https://www.youtube.com/watch?v=FxwPQkP3OGY&amp;t=611s">https://www.youtube.com/watch?v=FxwPQkP3OGY&amp;t=611s</a><br>
    <a href="https://timeweb.com/ru/community/articles/kak-ustanovit-stek-lamp-na-ubuntu-20-04">https://timeweb.com/ru/community/articles/kak-ustanovit-stek-lamp-na-ubuntu-20-04</a><br>
    <a href="https://wiki.merionet.ru/articles/perenos-bazy-dannyx-mysql-so-starogo-na-novyj-server">https://wiki.merionet.ru/articles/perenos-bazy-dannyx-mysql-so-starogo-na-novyj-server</a><br>
</p>