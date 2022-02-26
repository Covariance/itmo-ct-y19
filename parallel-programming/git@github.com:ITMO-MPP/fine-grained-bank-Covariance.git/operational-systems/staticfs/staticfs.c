#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivanov Ivan");
MODULE_DESCRIPTION("Static filesystem Linux module");
MODULE_VERSION("0.01");

struct timespec tm;

static int staticfs_iterate(struct file *filp, struct dir_context *ctx)
{
	return 0;
}

static struct file_operations staticfs_dir_operations = 
{
	.owner = THIS_MODULE,
	.iterate = staticfs_iterate,
};

static struct dentry *staticfs_lookup(struct inode *parent_inode, struct dentry *child_dentry, unsigned int flag)
{
	return NULL;
}

static struct inode_operations staticfs_inode_ops = 
{
	.lookup = staticfs_lookup,
};

struct inode *staticfs_get_inode(struct super_block *sb, const struct inode *dir, umode_t mode, dev_t dev, int i_ino)
{
	struct inode *inode = new_inode(sb);
	if (inode)
	{
		inode->i_ino = i_ino;
		inode_init_owner(inode, dir, mode);
		getnstimeofday(&tm);
		inode->i_atime = inode->i_mtime = inode->i_ctime = tm;
		switch (mode & S_IFMT)
		{
			case S_IFDIR:
				inc_nlink(inode);
				break;
			case S_IFREG:
			case S_IFLNK:
			default:
				printk(KERN_ERR "only root dir\n");
				return NULL;
				break;
		}
	}
	return inode;
}

int staticfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *inode;
	sb->s_magic = 0x12345678;
	inode = staticfs_get_inode(sb, NULL, S_IFDIR, 0, 100);
	inode->i_op = &staticfs_inode_ops;
	inode->i_fop = &staticfs_dir_operations;
	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
	{
		return -ENOMEM;
	}
	return 0;
}

static struct dentry *staticfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	struct dentry *ret;
	ret = mount_bdev(fs_type, flags, dev_name, data, staticfs_fill_super);
	if (unlikely(IS_ERR(ret)))
		printk(KERN_ERR "Error mounting staticfs");
	else
		printk(KERN_INFO "staticfs is successfully mounted on [%s]\n", dev_name);
	return ret;
}

static void staticfs_kill_superblock(struct super_block *s)
{
	printk(KERN_INFO "staticfs superblock is destroyed. Unmount successful.\n");
	return;
}

struct file_system_type staticfs_fs_type =
{
	.owner = THIS_MODULE,
	.name = "staticfs",
	.mount = staticfs_mount,
	.kill_sb = staticfs_kill_superblock,
};

static int staticfs_init(void)
{
	int ret;
	ret = register_filesystem(&staticfs_fs_type);
	if (likely(ret == 0))
		printk(KERN_INFO "Successfully registered staticfs\n");
	else
		printk(KERN_ERR "Failed to register staticfs. Error:[%d]", ret);
	return ret;
}

static void staticfs_exit(void)
{
	int ret;
	ret = unregister_filesystem(&staticfs_fs_type);
	if (likely(ret == 0))
		printk(KERN_INFO "Successfully unregistered staticfs\n");
	else
		printk(KERN_ERR "Failed to unregister staticfs. Error:[%d]\n", ret);
}

module_init(staticfs_init);
module_exit(staticfs_exit);
