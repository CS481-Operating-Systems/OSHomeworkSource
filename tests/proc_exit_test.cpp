#include "src.hpp"

FILE* fn;

void grandchild()
{
    fn = fopen("./procs.output", "w");
    int pid = getpid();
    fprintf(fn, "Grandchild %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void child()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Child %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void parent()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Parent %d\n", pid);
    fflush(fn);
    fclose(fn);
}

int main(int argc, char** argv)
{
    int pid = getpid();
    run_processes();

    fn = fopen("./procs.output", "r");

    char buff[255];
    int pid_g, pid_c, pid_p;
    fscanf(fn, "%s\n", buff);
    if (buff != "Grandchild")
        fprintf(stderr, "Grandchild process not running grandchild method first\n");
    fscanf(fn, "%d\n", &pid_g);
    fscanf(fn, "%s\n", buff);
    if (buff != "Child")
        fprintf(stderr, "Child process not running child method second\n");
    fscanf(fn, "%d\n", &pid_c);
    fscanf(fn, "%s\n", buff);
    if (buff != "Parent")
        fprintf(stderr, "Parent process not running parent method last\n");
    fscanf(fn, "%d\n", &pid_p);

    fclose(fn);

    if (pid != pid_p)
        fprintf(stderr, "A non-parent process forgot to exit\n");
    if (pid_p == pid_c)
        fprintf(stderr, "Parent and Child PIDs are the same\n");
    if (pid_p == pid_g)
        fprintf(stderr, "Parent and Grandchild PIDs are the same\n");
    if (pid_c == pid_g)
        fprintf(stderr, "Child and Grandparent PIDs are the same\n");

    return 0;
}



