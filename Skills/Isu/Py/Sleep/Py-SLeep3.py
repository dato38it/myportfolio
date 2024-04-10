#Использование time.sleep() в threading
import logging
import threading
import time
def worker(arg):
    while not arg["stop"]:
        logging.debug("рабочий поток вносится")
        time.sleep(1)
def main():
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(relativeCreated)6d %(threadName)s %(message)s"
    )
    info = {"stop": False}
    thread = threading.Thread(target=worker, args=(info,))
    thread_two = threading.Thread(target=worker, args=(info,))
    thread.start()
    thread_two.start()
    while True:
        try:
            logging.debug("Добавление из главного потока")
            time.sleep(0.75)
        except KeyboardInterrupt:
            info["stop"] = True
            logging.debug('Остановка')
            break
    thread.join()
    thread_two.join()
if __name__ == "__main__":
    main()
