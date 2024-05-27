from aiogram.types import (ReplyKeyboardMarkup, KeyboardButton, InlineKeyboardMarkup, InlineKeyboardButton)
from aiogram.utils.keyboard import ReplyKeyboardBuilder, InlineKeyboardBuilder
#main = ReplyKeyboardMarkup(keyboard=[
#                                [KeyboardButton(text='Catalog')],
#                                [KeyboardButton(text='Корзина'), KeyboardButton(text='Contacts')]
#                            ],
#                            resize_keyboard=True,
#                            input_field_placeholder='Выберите пункт меню')
main = InlineKeyboardMarkup(inline_keyboard=[
    [InlineKeyboardButton(text='Catalog', callback_data='catalog')],
    [InlineKeyboardButton(text='Basket', callback_data='basket'),
     InlineKeyboardButton(text='Contacts', callback_data='contacts')]
])
settings = InlineKeyboardMarkup(inline_keyboard=[
                                    [InlineKeyboardButton(text='Youtube', url='https://youtube.com/@sudoteach')]
                            ])
cars = ['Tesla', 'Mesredes', 'BMW']
async def inline_cars():
    keyboard = InlineKeyboardBuilder()
    for car in cars:
        keyboard.add(InlineKeyboardButton(text=car, url='https://youtube.com/@sudoteach'))
    return keyboard.adjust(2).as_markup()