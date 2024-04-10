#Системному администратору всегда нужно быть в курсе, если какой-то из сайтов упал. Вы бы хотели иметь возможность проверить код состояния сайта регулярно, но запрашивать веб сервер постоянно нельзя, ведь это сильно повлияет на производительность. В Python одним из простых способов совершить такую проверку является использование системного вызова sleep()
import time
import urllib.request
import urllib.error
def uptime_bot(url):
    while True:
        try:
            conn = urllib.request.urlopen(url)
        except urllib.error.HTTPError as e:
            # Отправка admin / log
            print(f'HTTPError: {e.code} для {url}')
        except urllib.error.URLError as e:
            # Отправка admin / log
            print(f'URLError: {e.code} для {url}')
        else:
            # Сайт поднят
            print(f'{url} поднят')
        time.sleep(60)
if __name__ == '__main__':
    url = 'http://www.google.com'
    uptime_bot(url)
