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
    int pid;
    run_processes();

    // Sleep for half a second in case parent returns
    // while children are still running
    sleep(0.5);

    fn = fopen("./procs.output", "r");

    char buff[255];
    int pid_g, pid_c, pid_p;
    fscanf(fn, "%s\n", buff);
    fscanf(fn, "%d\n", &pid_g);
    fscanf(fn, "%s\n", buff);
    fscanf(fn, "%d\n", &pid_c);
    fscanf(fn, "%s\n", buff);
    fscanf(fn, "%d\n", &pid_p);

    fclose(fn);

    if (pid_p == pid_c)
        fprintf(stderr, "Parent and Child PIDs are the same\n");
    if (pid_p == pid_g)
        fprintf(stderr, "Parent and Grandchild PIDs are the same\n");
    if (pid_c == pid_g)
        fprintf(stderr, "Child and Grandparent PIDs are the same\n");

    return 0;

}



