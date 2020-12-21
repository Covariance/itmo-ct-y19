# Задание 5. Статическая файловая система в Linux (20 баллов)

Использование модулей в Linux позволяет создавать свои файловые системы. В этом задании наша цель создать свою статическую файловую систему — такую, в которой список файлов и директорий постоянен и известен заранее. 

> Задание необходимо выполнить в ветке `staticfs`.

## Подзадание 1. Подготовка

Давайте создадим директорию, в которую и будем монтировать нашу файловую систему. Для этого выполним следующие команды:

```sh
$ mkdir ./ct/
$ dd bs=4096 count=100 if=/dev/zero of=image
```

Мы в текущей директории создали директорию `./ct/`, которая и будет точкой входа нашей файловой системы, а также скопировали в файл `image` 4096 × 100 нулевых байтов. Файл нам нужен, чтобы хранить данные ФС.

Теперь соберём наш модуль из файла [`staticfs.c`](staticfs.c). [`Makefile`](Makefile) останется таким же, как и в прошлом задании. Нам необходимо загрузить модуль и примонтировать нашу директорию:

```sh
$ sudo make
$ sudo insmod staticfs.ko
$ sudo mount -o loop -t staticfs image ./ct/
$ dmesg
[  123.456789] Successfully registered staticfs
[  123.456789] staticfs is successfully mounted on [/dev/loop0]
```

Изначально у директории `ct` не окажется никаких прав доступа — это можно проверить командой `ls -l`. Давайте изменим права этой директории, чтобы зайти в неё.

```sh
$ sudo chmod 777 ./ct/
$ cd ./ct/
$ ls
$
```

Мы смогли зайти в нашу файловую систему. Правда, файлов там нет, и `ls` закономерно ничего не вывела. Теперь отмонтируем нашу файловую систему и выгрузим модуль.

```sh
$ sudo umount ./ct/
$ sudo rmmod staticfs
```

## Подзадание 2. Вывод файлов и директорий

В этом подзадании мы начнём реализовывать структуру файловой системы: наша цель — научить утилиту `ls` корректно выводить список файлов и директорий. Структура ФС будет вот такой:

```
- dir/
  - file.txt
- file.txt
- test.txt
```

Начнём с корня файловой системы. Чтобы системный вызов `readdir` (которым пользуется `ls`) заработал корректно, нам необходимо изменить функцию `staticfs_iterate`. Приведём простой пример для одного файла:

```c
static int staticfs_iterate(struct file *filp, struct dir_context *ctx)
{
	char fsname[10];
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *i = dentry->d_inode;
	unsigned long offset = filp->f_pos;
	int stored = 0;
	unsigned char ftype;
	ino_t ino = i->i_ino;
	ino_t dino;	
	while (true)
	{
		if (ino == 100)
		{
			if (offset == 0)
			{
				strcpy(fsname, ".");
				ftype = DT_DIR;
				dino = ino;
			} 
			else if (offset == 1)
			{
				strcpy(fsname, "..");
				ftype = DT_DIR;
				dino = dentry->d_parent->d_inode->i_ino;
			}
			else if (offset == 2)
			{
				strcpy(fsname, "test.txt");
				ftype = DT_REG;
				dino = 101;
			}
			else
			{
				return stored;
			}
		}	
		dir_emit(ctx, fsname, strlen(fsname), dino, ftype);
		stored++;
		offset++;
		ctx->pos = offset;
	}
	return stored;
}
```

> Обратите внимание, что всегда необходимо корректно определять псевдодиректории: `.` — текущая папка, а `..` — родительская.

Попробуем снова вызвать `ls`:

```sh
$ ls -1
ls: cannot access 'test.txt': No such file or directory
test.txt
```

На самом деле, `ls` не только читает список файлов, но и узнаёт о них некую метаинформацию. Мы сказали, что файлу `test.txt` соответствует inode с номером 101, но про эту inode ничего больше не известно, отсюда и появляется ошибка. Мы исправим её в следующем подзадании.

Допишите функцию: добавьте ещё один файл `file.txt` и директорию `dir`. Обратите внимание, что `dir` должна быть именно директорией, а не файлом.

```sh
$ ls -1
<...>
dir
file.txt
test.txt
```

## Подзадание 3. Переход по директориям

После выполнения прошлого подзадания появилась куча ошибок. Чтобы научить файловую систему искать нужные нам файлы, исправим функцию `staticfs_lookup` — она находит в директории нужный файл. Пример для одного файла:

```c
static struct dentry *staticfs_lookup(struct inode *parent_inode, struct dentry *child_dentry, unsigned int flag)
{
	ino_t root = parent_inode->i_ino;
	const char *name = child_dentry->d_name.name;
	struct inode *inode;
	if (root == 100 && !strcmp(name, "test.txt"))
	{
		inode = staticfs_get_inode(parent_inode->i_sb, NULL, S_IFREG, 0, 101);
		inode->i_op = &staticfs_inode_ops;
		inode->i_fop = NULL;
		d_add(child_dentry, inode);
	}
	return NULL;
}
```

Попробуем собрать наш модуль и примонтируем нашу файловую систему:

```sh
$ ls -1
ls: cannot access 'file.txt': No such file or directory
ls: cannot access 'dir': No such file or directory
dir
file.txt
test.txt
$
```

Теперь ошибка с файлом `test.txt` исчезла. Завершите исправление: уберите все ошибки, а также реализуйте переход в директорию `dir`:

```sh
$ ls -1
dir
file.txt
test.txt
$ cd dir
$ ls -1
file.txt
$
```

> Помните, что вам нужно для `dir` написать как `staticfs_lookup` (чтобы в неё можно было перейти), так и `staticfs_iterate` (чтобы внутри неё можно было увидеть файлы).

## Подзадание 4. Операции с файлами

Вы помните, что после каждого монтирования ФС права на файлы не выдаются — их нужно добавлять руками. Сделайте так, чтобы права на все файлы по умолчанию были равны 777 — все могут делать любые операции.

* Для этого нужно изменить функцию `staticfs_get_inode`

Реализуем файловые операции. Для этого добавим в наш код следующую структуру и функцию, которая ничего не возвращает.

```c
static struct file_operations staticfs_file_operations = 
{
	.read = staticfs_read,
};

static ssize_t staticfs_read(struct file *flip, char *buffer, size_t len, loff_t *offset) 
{
	return 0;
}
```

Изменим `staticfs_lookup` так, чтобы рассказать операционной системе о новой доступной операции:

```c
if (root == 100 && !strcmp(name, "test.txt"))
{
	inode = staticfs_get_inode(parent_inode->i_sb, NULL, S_IFREG, 0, 101);
	inode->i_op = &staticfs_inode_ops;
	inode->i_fop = &staticfs_file_operations;
	d_add(child_dentry, inode);
}	
```

Теперь мы можем прочитать файл, но он пуст. Вспомните прошлое задание и модифицируйте файловую систему, добавив чтение и запись файлов.

```sh
$ cat test.txt
test
$ cat file.txt
Merry Christmas!
$ echo "Happy New Year!" > file.txt
$ cat file.txt
Happy New Year!
$ cat dir/file.txt
Merry Christmas!
$ echo "y2019" > dir/file.txt
$ cat dir/file.txt
y2019
$
```

* Файл `test.txt` должен всегда содержать строку `test`, запись недоступна.
* Файлы `file.txt` и `dir/file.txt` должны изначально хранить строку `Merry Christmas!` и давать возможность перезаписать эту строку
  * Содержимое файлов должно быть независимо.
* Размера буфера в 64 символа достаточно.

Тесты можно запустить вот так:

```sh
$ make tests
```

* Обратите внимание, что тесты монтируют вашу ФС в `/tmp/staticfs` и запускают всё там.

## Подзадание 5*. Удаление файлов (+3 балла)

> В этот раз можно выполнить три бонусных задания на выбор. Вы можете сделать любое их число, баллы суммируются. Правила те же — сдавать можно только вместе с основным.

Реализуйте удаление файлов без возможности восстановления.

```sh
$ rm file.txt
$ ls
dir
test.txt
```

* Для этого нужно добавить ещё одну функцию в `inode_operations`.
* Поддержка удаления нужна только для файлов из основного задания. Уметь удалять директории, а также файлы и директории из подзаданий 6 и 7 не нужно.

Чтобы запустить тесты, используйте Make-таргет:

```
$ make bonus-remove
```

## Подзадание 6*. Динамический файл (+2 балла)

Добавьте файл `netfile` в корень ФС, который будет отправлять данные на сервер при записи и получать их обратно при чтении.

Файловый сервер доступен [по ссылке](https://nerc.itmo.ru/teaching/os/staticfs/). Чтобы получить данные с сервера, сделайте GET-запрос на `https://nerc.itmo.ru/teaching/os/staticfs/YOURKEY/file`, где `YOURKEY` — ключ, который можно получить на сервере. Например, так:

```sh
curl https://nerc.itmo.ru/teaching/os/staticfs/YOURKEY/file
```

Чтобы сохранить данные на сервер, сделайте POST-запрос на тот же адрес, передав в теле запроса данные. Например, так:

```sh
curl -X POST -d NEWCONTENTHERE https://nerc.itmo.ru/teaching/os/staticfs/YOURKEY/file
```

В этом запросе кроме `YOURKEY` нужно также заменить `NEWCONTENTHERE` на новое содержимое файла. Слово `POST` менять не нужно — это тип запроса.

Чтобы запустить тесты, либо добавьте ваш ключ в седьмую строку `Makefile`, либо передавайте его в команде:

```
$ # ключ в Makefile
$ make bonus-netfile
$ # ключ в аргументах
$ make bonus-netfile FS_TOKEN=YOURKEY
```

## Подзадание 7*. Динамическая директория (+3 балла)

Добавьте директорию `netdir` в корень ФС, список файлов в которой будет читаться с сервера. Никакие операции с файлами (чтение, запись, удаление) внутри можно не поддерживать, но ошибок быть не должно:

```
$ cd netdir
$ ls
file1.txt
file2.txt
file3.txt
```

Директории хранятся на том же сервере. GET-запрос на `https://nerc.itmo.ru/teaching/os/staticfs/YOURKEY/list` возвращает список файлов, по одному на строке:

```
$ curl https://nerc.itmo.ru/teaching/os/staticfs/YOURKEY/list
file1.txt
file2.txt
file3.txt
```

Вы можете самостоятельно изменить список файлов, зайдя на сервер и введя новый список в соответствующее поле.

Чтобы запустить тесты, также понадобится ключ:

```
$ make bonus-netdir
$ # или
$ make bonus-netdir FS_TOKEN=YOURKEY
```
