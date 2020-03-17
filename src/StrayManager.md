#### reintegrate_stray()

如果有多个hardlink指向一个inode，而且这个inode 的primary dentry被删掉，这个inode就会有一个stray-primary dentry。此时我们会稍后重建（reintegrate）这个inode的dentry，使其有一个non-stray dentry，这个dentry就是之前remote denry中的一个。这个过程就是通过发起rename来完成的。

#### _eval_stray()

评估一个stray dentry，用来purging或者reintegration（重建）。
（1）	如果这个inode 已经没有linkage，也米有references，我们就可以决定purge（清理）掉。（2）如果这个inode 还有linkage，表示有其他的的引用（比如hardlink），此时可能就需要重建。
只有primary的linkage才会被评估。并且dentry对应的dir必须是stray目录。检查dn对应的lease，dentry中的lease 是一个map。以及inode对应的cap是否都已经回收。inode中的cap是一个map。
