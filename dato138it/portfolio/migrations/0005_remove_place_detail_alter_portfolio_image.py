# Generated by Django 5.0.2 on 2024-02-25 05:29

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('portfolio', '0004_place_detail'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='place',
            name='detail',
        ),
        migrations.AlterField(
            model_name='portfolio',
            name='image',
            field=models.ImageField(blank=True, null=True, upload_to='uploads/%Y/%m/%d/'),
        ),
    ]
