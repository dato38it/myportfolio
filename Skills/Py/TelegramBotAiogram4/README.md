# Telegram bot 4
Task:
Первый обработчик
Decision:
$ python3 -m venv pyenv
$ source pyenv/bin/activate
$ touch requirements.txt
$ vim requirements.txt
$ cat requirements.txt 
aiogram==3.4.1
$ pip install -r requirements.txt
- tetegram - BotFather - /start - /newbot - Tbot - tnlobot
$ touch main.py
$ vim main.py
$ cat main.py
import asyncio
from aiogram import Bot, Dispatcher
from aiogram.types import Message
bot = Bot(token='7153496019:AAG0XeyOSWEf8c8-k_9USF7ZIT7QXjM1BS4')
dp = Dispatcher()
@dp.message()
async def cmd_start(message: Message):
    await message.answer('Hey!')
    await message.reply('How are you')
async def main():
    await dp.start_polling(bot)
if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print('Bot disabled')
$ python main.py
- /start
Hey!
How are you
- hfhfgh
Hey!
How are you
Task:
Фильтры
Decision:
$ vim main.py
$ cat main.py
import asyncio
from aiogram import Bot, Dispatcher, F
from aiogram.types import Message
from aiogram.filters import CommandStart, Command
...
#@dp.message()
@dp.message(CommandStart())
async def cmd_start(message: Message):
    await message.answer('Hey!')
    await message.reply('How are you')
@dp.message(Command('help'))
async def cmd_help(message: Message):
    await message.answer('You clicked helps button')
@dp.message(F.text == 'Im ok')
async def nice(message: Message):
    await message.answer('Its cool')
...
$ python main.py
- /start
Hey!
How are you
- Im ok
Its cool
- hfhfgh
- /help
You clicked helps button
Task:
роутеры
Decision:
$ mkdir app
$ touch app/handlers.py
$ vim app/handlers.py
$ cat app/handlers.py
from aiogram import F, Router
from aiogram.types import Message
from aiogram.filters import CommandStart, Command
router = Router()
#@router.message()
@router.message(CommandStart())
async def cmd_start(message: Message):
    await message.answer('Hey!')
    await message.reply('How are you')
@router.message(Command('help'))
async def cmd_help(message: Message):
    await message.answer('You clicked helps button')
@router.message(F.text == 'Im ok')
async def nice(message: Message):
    await message.answer('Its cool')
$ vim main.py
$ cat main.py
import asyncio
from aiogram import Bot, Dispatcher
from app.handlers import router
async def main():
    bot = Bot(token='7153496019:AAG0XeyOSWEf8c8-k_9USF7ZIT7QXjM1BS4')
    dp = Dispatcher()
    dp.include_router(router)
    await dp.start_polling(bot)
if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print('Bot disabled')
Task:
клавиатуры
Decision:  
$ touch app/keyboards.py
$ vim app/keyboards.py
$ cat app/keyboards.py
from aiogram.types import (ReplyKeyboardMarkup, 
                           KeyboardButton, 
                           InlineKeyboardMarkup, 
                           InlineKeyboardButton)
main = ReplyKeyboardMarkup(keyboard=[[KeyboardButton(text='Каталог')],
                                     [KeyboardButton(text='Корзина')],
                                     [KeyboardButton(text='Контакты'),
                                      KeyboardButton(text='О нас')]],
                            resize_keyboard=True,
                            input_field_placeholder='Выберите пункт меню...')
catalog = InlineKeyboardMarkup(inline_keyboard=[[InlineKeyboardButton(text='Футболки', callback_data='t-shirt')],
                                                [InlineKeyboardButton(text='Кроссовки', callback_data='sneakers')],
                                                [InlineKeyboardButton(text='Кепки', callback_data='cap')]])
$ vim app/handlers.py
$ cat app/handlers.py
...
import app.keyboards as kb
..
@router.message(CommandStart())
async def cmd_start(message: Message):
    #await message.answer('Hey!')
    await message.answer('Hey!', reply_markup=kb.main)
    await message.reply('How are you')
...
#@router.message(F.text == 'Im ok')
#async def nice(message: Message):
#    await message.answer('Its cool')
@router.message(F.text == 'Каталог')
async def catalog(message: Message):
    await message.answer('Выберите категорю', reply_markup=kb.catalog)
$ python main.py
- /start
Hey!
How are you
Каталог, Корзина, Контакты, О нас
- Каталог
Выберите категорю
Футболки, Кроссовки, Кепки
Task:
CallBackQuery
Decision:
$ vim app/handlers.py
$ cat app/handlers.py
from aiogram import F, Router
from aiogram.types import Message, CallbackQuery
from aiogram.filters import CommandStart, Command
...
@router.callback_query(F.data == 't-shirt')
async def t_shirt(callback: CallbackQuery):
    await callback.answer('Вы выбрали категорию', show_alert=True)
    await callback.message.answer('Вы выбрали категорию футболок')
$ python main.py
- /start
Hey!
How are you
Каталог, Корзина, Контакты, О нас
- Каталог
Выберите категорю
Футболки, Кроссовки, Кепки
- Футболки
Вы выбрали категорию футболок
Task:
Состояния
Decision:
$ vim app/handlers.py
$ cat app/handlers.py
...
from aiogram.fsm.state import State, StatesGroup
from aiogram.fsm.context import FSMContext
import app.keyboards as kb
router = Router()
router = Router()
class Register(StatesGroup):
    name = State()
    age = State()
    number = State()
#@router.message()
...
@router.message(Command('register'))
async def register(message: Message, state: FSMContext):
    await state.set_state(Register.name)
    await message.answer('Введите ваше имя:')
@router.message(Register.name)
async def register(message: Message, state: FSMContext):
    await state.update_data(name=message.text)
    await state.set_state(Register.age)
    await message.answer('Введите ваше возраст:')
@router.message(Register.age)
async def register(message: Message, state: FSMContext):
    await state.update_data(age=message.text)
    await state.set_state(Register.number)
    await message.answer('Введите ваше номер телефона:', reply_markup=kb.get_number)
@router.message(Register.number, F.contact)
async def register_number(message: Message, state: FSMContext):
    await state.update_data(number=message.contact.phone_number)
    data= await state.get_data()
    await message.answer(f'Your name: {data["name"]}\nYour age: {data["age"]}\nYour number: {data["number"]}')
    await state.clear()
$ vim app/keyboards.py
$ cat app/keyboards.py
...
get_number = ReplyKeyboardMarkup(keyboard=[[KeyboardButton(text='Отправить номер', request_contact=True)]],
                                 resize_keyboard=True)
$ python main.py
- /start
Hey!
How are you
Каталог, Корзина, Контакты, О нас
- /register
Введите ваше имя:
- tuser
Введите ваше возраст:
- 30
Введите ваше номер телефона:
- Отправить номер
Your name: tuser
Your age: 30
Your number: tnumber
Task:
Создание моделей таблиц
Decision:
$ mkdir app/database
$ vim requirements.txt
$ cat requirements.txt 
aiogram==3.4.1
sqlalchemy==2.0.30
aiosqlite==0.20.0
$ pip install -r requirements.txt
$ touch app/database/models.py
$ vim app/database/models.py
$ cat app/database/models.py
from sqlalchemy import BigInteger, String, ForeignKey
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column
from sqlalchemy.ext.asyncio import AsyncAttrs, async_sessionmaker, create_async_engine
engine = create_async_engine(url='sqlite+aiosqlite:///db.sqlite3')
async_session = async_sessionmaker(engine)
class Base(AsyncAttrs, DeclarativeBase):
    pass
class User(Base):
    __tablename__ = 'users'
    id: Mapped[int] = mapped_column(primary_key=True)
    tg_id = mapped_column(BigInteger)
class Category(Base):
    __tablename__ = 'categories'
    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(25))
class Item(Base):
    __tablename__ = 'items'
    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(String(25))
    description: Mapped[str] = mapped_column(String(120))
    price: Mapped[int] = mapped_column()
    category: Mapped[int] = mapped_column(ForeignKey('categories.id'))
async def async_main():
    async with engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)
$ vim main.py
$ cat main.py
...
from app.database.models import async_main
async def main():
    await async_main()
    ...
$ python main.py
$ sqlite3 db.sqlite3 
sqlite> .tables
categories  items       users     
sqlite> select * from categories;
sqlite> .q
Task:
Запросы и хэндлеры
Decision:
$ touch app/database/requests.py
$ vim app/database/requests.py
$ cat app/database/requests.py
from app.database.models import async_session
from app.database.models import User, Category, Item
from sqlalchemy import select
async def set_user(tg_id):
    async with async_session() as session:
        user = await session.scalar(select(User).where(User.tg_id == tg_id))
        if not user:
            session.add(User(tg_id=tg_id))
            await session.commit()
$ vim app/handlers.py
$ cat app/handlers.py         
...
import app.database.requests as rq
...
@router.message(CommandStart())
async def cmd_start(message: Message):
    #await message.answer('Hey!')
    #await message.answer('Hey!', reply_markup=kb.main)
    #await message.reply('How are you')
    await rq.set_user(message.from_user.id)
    await message.answer('Добро пожаловать в магазин кроссовок!', reply_markup=kb.main)
...
$ python main.py
- /start
Добро пожаловать в магазин кроссовок!
$ sqlite3 db.sqlite3 
sqlite> select * from users;
1|1064831036
sqlite> .q
Decision:
sqlite> select * from categories;
1|Adidas
2|Nike
3|Forward
sqlite> select * from items;
1|name1|desc1|50|3
2|name2|desc2|75|1
3|name3|desc3|50|2
$ vim app/keyboards.py
$ cat app/keyboards.py
from aiogram.types import (ReplyKeyboardMarkup, 
                           KeyboardButton, 
                           InlineKeyboardMarkup, 
                           InlineKeyboardButton)
from aiogram.utils.keyboard import InlineKeyboardBuilder
from app.database.requests import get_categories, get_category_item
main = ReplyKeyboardMarkup(keyboard=[[KeyboardButton(text='Каталог')],
                                     [KeyboardButton(text='Корзина')],
                                     [KeyboardButton(text='Контакты'),
                                      KeyboardButton(text='О нас')]],
                            resize_keyboard=True,
                            input_field_placeholder='Выберите пункт меню...')
'''
catalog = InlineKeyboardMarkup(inline_keyboard=[[InlineKeyboardButton(text='Футболки', callback_data='t-shirt')],
                                                [InlineKeyboardButton(text='Кроссовки', callback_data='sneakers')],
                                                [InlineKeyboardButton(text='Кепки', callback_data='cap')]])

get_number = ReplyKeyboardMarkup(keyboard=[[KeyboardButton(text='Отправить номер', request_contact=True)]],
                                 resize_keyboard=True)
'''
async def categories():
    all_categories = await get_categories()
    keyboard = InlineKeyboardBuilder()
    for category in all_categories:
        keyboard.add(InlineKeyboardButton(text=category.name, callback_data=f"category_{category.id}"))
    keyboard.add(InlineKeyboardButton(text='На главную', callback_data='to_main'))
    return keyboard.adjust(2).as_markup()
async def items(category_id):
    all_items = await get_category_item(category_id)
    keyboard = InlineKeyboardBuilder()
    for item in all_items:
        keyboard.add(InlineKeyboardButton(text=item.name, callback_data=f"item_{item.id}"))
    keyboard.add(InlineKeyboardButton(text='На главную', callback_data='to_main'))
    return keyboard.adjust(2).as_markup()
$ vim app/handlers.py
$ cat app/handlers.py
from aiogram import F, Router
from aiogram.types import Message, CallbackQuery
from aiogram.filters import CommandStart, Command
from aiogram.fsm.state import State, StatesGroup
from aiogram.fsm.context import FSMContext
import app.keyboards as kb
import app.database.requests as rq
router = Router()
'''
class Register(StatesGroup):
    name = State()
    age = State()
    number = State()
'''
#@router.message()
@router.message(CommandStart())
async def cmd_start(message: Message):
    #await message.answer('Hey!')
    #await message.answer('Hey!', reply_markup=kb.main)
    #await message.reply('How are you')
    await rq.set_user(message.from_user.id)
    await message.answer('Добро пожаловать в магазин кроссовок!', reply_markup=kb.main)
'''
@router.message(Command('help'))
async def cmd_help(message: Message):
    await message.answer('You clicked helps button')
#@router.message(F.text == 'Im ok')
#async def nice(message: Message):
#    await message.answer('Its cool')
@router.message(F.text == 'Каталог')
async def catalog(message: Message):
    await message.answer('Выберите категорю', reply_markup=kb.catalog)
@router.callback_query(F.data == 't-shirt')
async def t_shirt(callback: CallbackQuery):
    await callback.answer('Вы выбрали категорию', show_alert=True)
    await callback.message.answer('Вы выбрали категорию футболок')
@router.message(Command('register'))
async def register(message: Message, state: FSMContext):
    await state.set_state(Register.name)
    await message.answer('Введите ваше имя:')
@router.message(Register.name)
async def register(message: Message, state: FSMContext):
    await state.update_data(name=message.text)
    await state.set_state(Register.age)
    await message.answer('Введите ваше возраст:')
@router.message(Register.age)
async def register(message: Message, state: FSMContext):
    await state.update_data(age=message.text)
    await state.set_state(Register.number)
    await message.answer('Введите ваше номер телефона:', reply_markup=kb.get_number)
@router.message(Register.number, F.contact)
async def register_number(message: Message, state: FSMContext):
    await state.update_data(number=message.contact.phone_number)
    data= await state.get_data()
    await message.answer(f'Your name: {data["name"]}\nYour age: {data["age"]}\nYour number: {data["number"]}')
    await state.clear()
'''
@router.message(F.text == 'Каталог')
async def catalog(message: Message):
    await message.answer('Выберите категорю товара', reply_markup=await kb.categories())
@router.callback_query(F.data.startswith('category_'))
async def category(callback: CallbackQuery):
    await callback.answer('Вы выбрали категорию')
    await callback.message.answer('Выберите товар по категории', 
                                  reply_markup=await kb.items(callback.data.split('_')[1]))
@router.callback_query(F.data.startswith('item_'))
async def category(callback: CallbackQuery):
    item_data = await rq.get_item(callback.data.split('_')[1])
    await callback.answer('Вы выбрали товар')
    await callback.message.answer(f'Навзвание: {item_data.name}\nОписание: {item_data.description}\nЦена: {item_data.price}$', 
                                  reply_markup=await kb.items(callback.data.split('_')[1]))
$ vim app/database/requests.py
$ cat app/database/requests.py
...
async def get_categories():
    async with async_session() as session:
        return await session.scalars(select(Category))
async def get_category_item(category_id):
    async with async_session() as session:
        return await session.scalars(select(Item).where(Item.category == category_id))
async def get_item(item_id):
    async with async_session() as session:
        return await session.scalar(select(Item).where(Item.id == item_id))
$ python main.py
- /start
Добро пожаловать в магазин кроссовок!
- Каталог
Выберите категорию товара
Adidas, Nike, Forward, На главную
- Adidas
Выберите товар по категории
name1, На главную
- name1
Название: name1
Описание: desc1
Цена: 50$
name2, На главную
Task:
PostgreSQL, Скрытие Токена в .env
Decision:
$ vim requirements.txt
$ cat requirements.txt 
aiogram==3.4.1
sqlalchemy==2.0.30
aiosqlite==0.20.0
python-dotenv==1.0.1
psycopg2==2.9.9
asyncpg==0.29.0
$ pip3 install -r requirements.txt
$ touch .env
$ vim .env
$ cat .env
TOKEN=7153496019:AAG0XeyOSWEf8c8-k_9USF7ZIT7QXjM1BS4
#SQLALCHEMY_URL=sqlite+aiosqlite:///db.sqlite3
#SQLALCHEMY_URL=postgresql+psycopg2:///user:password@host:port/dbname
SQLALCHEMY_URL=postgresql+asyncpg:///tuser:tpassword@192.168.122.98:5432/tdb
$ touch .gitignore
$ vim .gitignore
$ cat .gitignore
.env
$ vim main.py
$ cat main.py
...
import os
from dotenv import load_dotenv
async def main():
    await async_main()
    #bot = Bot(token='7153496019:AAG0XeyOSWEf8c8-k_9USF7ZIT7QXjM1BS4')
    load_dotenv()
    bot = Bot(token=os.getenv('TOKEN'))    
    ...
$ vim app/database/models.py
$ cat app/database/models.py
...
import os
from dotenv import load_dotenv
#engine = create_async_engine(url='sqlite+aiosqlite:///db.sqlite3')
load_dotenv()
engine = create_async_engine(url=os.getenv('SQLALCHEMY_URL'))
...
$ psql -U tuser -d tdb -h 192.168.122.98
$ CREATE DATABASE shop;
$ python main.py
...
asyncpg.exceptions.InvalidCatalogNameError: database "tuser:tpassword@192.168.122.98:5432/tdb" does not exist
Source:
Телеграм Бот на Python с нуля - https://www.youtube.com/watch?v=7mdyOUjECP0&list=PLV0FNhq3XMOJ31X9eBWLIZJ4OVjBwb-KM&index=8