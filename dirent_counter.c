#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/param.h>
#include <string.h>
/* 
 * recursively count the number of directory entries and report.
 */
int scan(const char *dirpath);

int main(int argc, char *argv[]) 
{
	if (argc<=1) {
		fprintf(stderr, "usage %s dir", argv[0]);
		return 1;
	}
	scan(argv[1]);
	return 0;
}

int scan(const char *dirpath) 
{
        DIR *dir;

	dir=opendir(dirpath);
	if (dir==NULL) {
		perror(dirpath);
	} else {
		struct dirent *ent;
		int count=0;

		while((ent=readdir(dir))) {
			if (strcmp(ent->d_name, ".")==0) {
				/* ignore */
			} else if (strcmp(ent->d_name, "..")==0) {
				/* ignore */
			} else if (ent->d_type==DT_DIR) {
				char path[MAXPATHLEN];

				if (dirpath[strlen(dirpath)-1]=='/') {
					snprintf(path, MAXPATHLEN, "%s%s", dirpath, ent->d_name);
				} else {
					snprintf(path, MAXPATHLEN, "%s/%s", dirpath, ent->d_name);
				}
				scan(path);
			}	
			count++;
		} 
		closedir(dir);

		/* report */
		printf("%d\t%s\n", count, dirpath);
	}
	
	return 0;
}
