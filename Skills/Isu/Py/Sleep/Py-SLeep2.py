#Вызов sleep() с декораторами
import time
import urllib.request
import urllib.error
def sleep(timeout, retry=3):
    def the_real_decorator(function):
        def wrapper(*args, **kwargs):
            retries = 0
            while retries < retry:
                try:
                    value = function(*args, **kwargs)
                    if value is None:
                        return
                except:
                    print(f'Сон на {timeout} секунд')
                    time.sleep(timeout)
                    retries += 1
        return wrapper
    return the_real_decorator
@sleep(3)
def uptime_bot(url):
    try:
        conn = urllib.request.urlopen(url)
    except urllib.error.HTTPError as e:
        # Отправка admin / log
        print(f'HTTPError: {e.code} для {url}')
        # Повторное поднятие ошибки исключения для декоратора
        raise urllib.error.HTTPError
    except urllib.error.URLError as e:
        # Отправка admin / log
        print(f'URLError: {e.code} для {url}')
        # Повторное поднятие ошибки исключения для декоратора
        raise urllib.error.URLError
    else:
        # Сайт поднят
        print(f'{url} поднят')
if __name__ == '__main__':
    url = 'http://www.google.com/py'
    uptime_bot(url)
