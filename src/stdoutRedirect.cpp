#include "stdoutRedirect.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int outfd;
static int errfd;
static int infd;

static fpos_t outpos;
static fpos_t errpos;
static fpos_t inpos;

void switchStdout(const char *newStream)
{
  fflush(stdout);
  fgetpos(stdout, &outpos);
  outfd = _dup(STDOUT_FILENO);
  freopen(newStream, "w", stdout);
}

void revertStdout()
{
  fflush(stdout);
  _dup2(outfd, STDOUT_FILENO);
  close(outfd);
  clearerr(stdout);
  fsetpos(stdout, &outpos);
}

void switchStderr(const char *newStream)
{
  fflush(stderr);
  fgetpos(stderr, &errpos);
  errfd = _dup(STDERR_FILENO);
  freopen(newStream, "w", stderr);
}

void revertStderr()
{
  fflush(stderr);
  _dup2(errfd, STDERR_FILENO);
  close(errfd);
  clearerr(stderr);
  fsetpos(stderr, &errpos);
}


void switchStdin(const char *newStream)
{
  fflush(stdin);
  fgetpos(stdin, &inpos);
  infd = _dup(STDIN_FILENO);
  freopen(newStream, "w", stdin);
}


void revertStdin()
{
  fflush(stdin);
  _dup2(infd, STDIN_FILENO);
  close(infd);
  clearerr(stdin);
  fsetpos(stdin, &inpos);
}
