<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link href="https://fonts.googleapis.com/css?family=Kaushan+Script|Montserrat:300i,400,700&amp;subset=cyrillic-ext" rel="stylesheet">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/style.css">
    <link rel="stylesheet" href="css/blocks/container.css">
    <link rel="stylesheet" href="css/blocks/header.css">
    <link rel="stylesheet" href="css/blocks/nav.css">
    <link rel="stylesheet" href="css/blocks/intro.css">
    <link rel="stylesheet" href="css/blocks/btn.css">
    <link rel="stylesheet" href="css/blocks/section.css">
    <link rel="stylesheet" href="css/blocks/card.css">
    <link rel="stylesheet" href="css/blocks/adapter.css">  
    <link rel="stylesheet" href="css/blocks/footer.css">
    <link rel="stylesheet" href="css/blocks/copyright.css">
    <link rel="stylesheet" href="css/blocks/modal.css">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/npm/slick-carousel@1.8.1/slick/slick.css"/>
    <title>Contacts</title>
</head>
<body>
     <header class="header--color" id="header">
        <div class="container">
            <div class="header__inner">
                <div class="header__logo" data-scroll="#intro">Portfolio</div>
                <nav class="nav--colorWeb" id="nav--colorWeb">
                    <a class="nav__link--colorWeb" href="#" data-scroll="#contact">Контакты</a>

                </nav>
                <button class="nav-toggle" id="nav_toggle" type="button">
                    <span class="nav-toggle__item">Menu</span>
                </button>
            </div>
        </div>
    </header>  
    <div class="page">
        <!-- Intro -->
        <div class="intro--imgWeb" id="intro">
            <div class="container">
                <div class="intro__inner">
                    <h1 class="intro__title">Форма обратной связи</h1> 
                    <a class="btn" href="#" data-scroll="#contact">Контакты</a>
                </div>
            </div>
        </div><!-- /.intro -->
        <!--Footer-->
        <footer class="section--colorWeb" id="contact">
            <div class="container">
                <div class="section__header">
                     <h2 class="section__title--color">Контакты</h2>
                </div>
                <div class="footer__inner">
                    <div class="footer__col  footer__col--first">
                        <div class="footer__social">
                            <div class="footer__social-content">
                                <a href="#" target="_blank">
                                    <i class="fa fa-envelope"></i>
                                </a>
                                <a href="#" target="_blank">
                                    Dato138IT@yandex.ru
                                </a>
                            </div>
                        </div>
	                	<div class="footer__text">Задать вопрос:</div>
                      	<a name="form__anchor"></a>
                        <form action="http://myportfolio138.ru/www/Web-Form/index.php#form__anchor" method="post" name="f1"> 
	                    	<input class="footer__name" placeholder="Ваше имя" type="text" name="name1" required>
							<input class="footer__email" placeholder="Ваш Е-mail" type="email" name="email1" required="required">
							<textarea class="footer__textarea" placeholder="Ваш текст" name="text" required="required"></textarea>
							<input class="btn__formWeb" value="Отправить" type="submit" name="bttn">
						</form> 
                        <?php
                        $question="Question";
                        error_reporting( E_ERROR );   //Отключение предупреждений и нотайсов (warning и notice) на сайте
                        // создание переменных из полей формы		
                        if (isset($_POST['name1']))			{$name1			= $_POST['name1'];		if ($name1 == '')	{unset($name1);}}
                        if (isset($_POST['email1']))		{$email1		= $_POST['email1'];		if ($email1 == '')	{unset($email1);}}
                        if (isset($_POST['text']))			{$text			= $_POST['text'];		if ($text == '')	{unset($text);}}
                        if (isset($_POST['bttn']))			{$bttn			= $_POST['bttn'];		if ($bttn == '')		{unset($bttn);}}
                        //стирание треугольных скобок из полей формы
                        if (isset($name1) ) {
                        $name1=stripslashes($name1);
                        $name1=htmlspecialchars($name1);
                        }
                        if (isset($email1) ) {
                        $email1=stripslashes($email1);
                        $email1=htmlspecialchars($email1);
                        }
                        if (isset($text) ) {
                        $text=stripslashes($text);
                        $text=htmlspecialchars($text);
                        }
                        // адрес почты куда придет письмо
                        $address="Dato138IT@yandex.ru";
                        // текст письма 
                        $note_text="Тема : $question \r\nИмя : $name1 \r\n Email : $email1 \r\n Дополнительная информация : $text";

                        if (isset($name1)  &&  isset ($bttn) ) {
                        mail($address,$question,$note_text,"Content-type:text/plain; windows-1251"); 
                        // сообщение после отправки формы
                        echo "<div class='footer__text'><p style='margin-top: 10px;'>Уважаемый(ая) <b>$name1</b> Ваше письмо отправленно успешно.  Спасибо. Вам скоро ответят на почту <b> $email1</b>.</p></div>";
                        }
                        ?>
                    </div><!-- /.footer__col -->
                </div><!-- /.footer__inner -->
            </div><!--/.container-->
        </footer><!--/.Footer-->
        <!--copyright-->
        <div class="copyright--colorWeb">
            <div class="container">
                <div class="copyright__text">
                    © MyPortfolio, 2020, by <span>Dato</span>
                </div>
            </div>
        </div><!--/.copyright-->        
    </div><!-- /.page -->
<!-- JS -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
<script type="text/javascript" src="https://cdn.jsdelivr.net/npm/slick-carousel@1.8.1/slick/slick.min.js"></script>
<script src="js/main.js"></script>
</body>
</html>





