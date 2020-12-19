# Задание 5. Реализация статической файловой системы в Linux (20 баллов)

Использование модулей в Linux позволяет создавать свои файловые системы. В этом задании наша цель создать свою статическую файловую систему, т.е. список файлов и директорий постоянен и известен заранее. 

## Подзадание 1. Подготовка

Давайте создадим директорию, в которую и будем монтировать нашу файловую систему. Для этого выполним следующие команды:

```sh
$ mkdir ./ct/
$ dd bs=4096 count=100 if=/dev/zero of=image
```

Мы в текущей директории создали директорию `./ct/`, которая и будет точкой входа нашей файловой системы. Также с помощью команды `dd` мы скопировали в файл `image` 4096 * 100 нулевых байтов.

Давайте теперь соберём наш модуль из файла [`staticfs.c`](staticfs.c). [`Makefile`](Makefile) такой же, как и был в 4 задании. Также нам необходимо загрузить модуль и примонтировать нашу директорию:

```sh
$ sudo make
$ sudo insmod staticfs.ko
$ sudo mount -o loop -t staticfs image ./ct/
$ dmesg
[  123.456789] Successfully registered staticfs
[  123.456789] staticfs is successfully mounted on [/dev/loop0]
```

Поскольку мы не задавали права для нашего корня, то у директории `ct` нет никаких прав доступа (вы можете это проверить с помощью команды `ls -l`). Давайте изменим права этой директориии, тогда сможем смокойно перейти в директорию `ct`.

```sh
$ sudo chmod 777 ./ct/
$ cd ./ct/
$ ls
$
```

Таким образом мы сейчас зашли корень нашей файловой системы, но поскольку файлов нет, то и команда `ls` закономерно ничего не вывела. Теперь отмонтируем нашу файловую систему и выгрузим модуль.

```sh
$ sudo umount ./ct/
$ sudo rmmod staticfs
```

## Подзадание 2. Вывод файлов и директорий.

Теперь реализуем корректный вывод команды `ls`. Ваша файловая система должна иметь следующий вид:

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

Для начала реализуем команду ls, которая в директории `./ct/` будет выводить нужные нам файлы. Для этого необходимо изменить функцию `staticfs_iterate`. Ниже приведён пример, который выводит только один файл `test.txt`.

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

Заметьте, что необходимо также определять псевдодиректории `.` и `..` для корректной работы файловой системы. При попытке вызова команды `ls` в нашей директории `ct` мы получим следующий вывод:

```sh
$ ls -1
ls: cannot access 'test.txt': No such file or directory
test.txt
```

Это связано с тем, что на `test.txt` мы зарегистрировали `inode` с номером 101, но при этом система ничего не знает про файл с таким `inode`. Можете пока не обращать внимание на эту ошибку, позже мы её исправим.

Вам необходимо будет дописать функцию таким образом, чтобы выводились ещё файл `file.txt` и директория `dir`. Обратите внимание, что `dir` должна отображаться именно как директория.

```sh
$ ls -1
<...>
dir
file.txt
test.txt
```

## Подзадание 3. Исправление ошибок команды ls и реализация возможности перехода в директорию dir

При попытке вызова команды `ls` мы ловили ошибку связанную с тем, что при попытке системы прочитать файл она не находила его inode. Давайте исправим ошибку, связанную с файлом `test.txt`, для этого необходимо исправить функцию `staticfs_lookup`:

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

Теперь попробуем собрать наш модуль и примонтируем нашу файловую систему:

```sh
$ ls -1
ls: cannot access 'file.txt': No such file or directory
ls: cannot access 'dir': No such file or directory
dir
file.txt
test.txt
$
```

Обратите внимание, что теперь нет ошибки связанной с ошибкой доступа к файла `test.txt`. Вам предстоит сделать так, чтобы команда `ls` вообще не кидала ошибок, а также можно было зайти в директорию `dir`. Формально должны работать следующие команды:

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

> Для того, чтобы можно было зайти в директорию `dir` достаточно дописать только функцию `staticfs_lookup`, для корректной реализации `ls` внутри директории `dir` необходимо уже дописать `staticfs_iterate`.

## Подзадание 4. Реализация файловых операций

После монтирования файловой системы есть проблема, что у директории `ct` нет никаких прав доступа, поэтому приходится вручную вызывать команду `chmod`. Вам необходимо сделать так, чтобы у всех файлов в вашей статической файловой были возможны все операции для всех групп (т.е. 777).

> Достаточно лишь изменить функцию `staticfs_get_inode`

Теперь попробуем реализовать файловые операции. Для этого добавим в наш код следующую структуру:

```c
static struct file_operations staticfs_file_operations = 
{
	.read = staticfs_read,
};
```

И реализуем простую функцию, которая ничего не возвращает.

```c
static struct file_operations staticfs_file_operations = 
{
	.read = staticfs_read,
};
```

Также изменим немного функцию `staticfs_lookup`:

```c
if (root == 100 && !strcmp(name, "test.txt"))
{
	inode = staticfs_get_inode(parent_inode->i_sb, NULL, S_IFREG, 0, 101);
	inode->i_op = &staticfs_inode_ops;
	inode->i_fop = &staticfs_file_operations;
	d_add(child_dentry, inode);
}	
```

Вам необходимо релизовать файловую систему таким образом, чтобы были валидными следующими командами:

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

Формально файл `test.txt` при чтении всегда должен возвращать строку "test", а файлы `file.txt` и `dir/file.txt` должны по умолчанию хранить строку "Merry Christmas!", но при записи в них новых строк должны выводить её независимо друг от друга.
