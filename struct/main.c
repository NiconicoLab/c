#include <stdio.h>

struct person {
    char *name;
    int age;
    int (*func)(struct person *, int);
};

int update(struct person *p, int n)
{
    return (p->age + n);
}

int none(struct person *p, int n)
{
	return p->age;
}

struct person people[] = {
	{"sato",      20, update},
	{"tanaka",    21, update},
    {"suzuki",    22, none},
    {"takahashi", 23, none},
};

int main(int argc, char *argv[])
{
	if(argc != 1) {
		fprintf(stderr, "Usage $%s\n", argv[0]);
		return -1;
	}

    for (int i = 0; i < sizeof(people) / sizeof(struct person); i++) {
        struct person *p = &people[i];
        if (p->age <= 22) {
            int new_age = p->func(p, 5);
            printf("%s : %d\n", p->name, new_age);
        }
		else {
            printf("%s : %d\n", p->name, p->age);
        }
    }

    return 0;
}
