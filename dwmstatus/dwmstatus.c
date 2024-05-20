/*
 * Copy me if you can.
 * by 20h
 */

#define _BSD_SOURCE
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <X11/Xlib.h>

/* char *tz= "Asia/Shanghai"; */
char *tzlocal = "GMT-8";

static Display *dpy;

char *smprintf(char *fmt, ...)
{
  va_list fmtargs;
  char *ret;
  int len;

  va_start(fmtargs, fmt);
  len = vsnprintf(NULL, 0, fmt, fmtargs);
  va_end(fmtargs);

  ret = malloc(++len);
  if (ret == NULL)
  {
    perror("malloc");
    exit(1);
  }

  va_start(fmtargs, fmt);
  vsnprintf(ret, len, fmt, fmtargs);
  va_end(fmtargs);

  return ret;
}

void settz(char *tzname)
{
  setenv("TZ", tzname, 1);
}

char *mktimes(char *fmt, char *tzname)
{
  char buf[129];
  time_t tim;
  struct tm *timtm;

  settz(tzname);
  tim = time(NULL);
  timtm = localtime(&tim);
  if (timtm == NULL) return smprintf("");

  if (!strftime(buf, sizeof(buf) - 1, fmt, timtm))
  {
    fprintf(stderr, "strftime == 0\n");
    return smprintf("");
  }

  return smprintf("%s", buf);
}

void setstatus(char *str)
{
  XStoreName(dpy, DefaultRootWindow(dpy), str);
  XSync(dpy, False);
}


char *loadavg(void)
{
  double avgs[3];

  if (getloadavg(avgs, 3) < 0) return smprintf("");

  return smprintf("%.2f %.2f %.2f", avgs[0], avgs[1], avgs[2]);
}


char *readfile(char *base, char *file)
{
  char *path, line[513];
  FILE *fd;

  memset(line, 0, sizeof(line));

  path = smprintf("%s/%s", base, file);
  fd = fopen(path, "r");
  free(path);
  if (fd == NULL) return NULL;

  if (fgets(line, sizeof(line) - 1, fd) == NULL) return NULL;
  fclose(fd);

  return smprintf("%s", line);
}

char *getbattery(char *base)
{
  char *co, status;
  int descap, remcap;

  descap = -1;
  remcap = -1;

  co = readfile(base, "present");
  if (co == NULL) return smprintf("");
  if (co[0] != '1')
  {
    free(co);
    return smprintf("not present");
  }
  free(co);

  co = readfile(base, "energy_full_design");
  if (co == NULL)
  {
    co = readfile(base, "charge_full_design");
    if (co == NULL) return smprintf("");
  }
  sscanf(co, "%d", &descap);
  free(co);

  co = readfile(base, "energy_now");
  if (co == NULL)
  {
    co = readfile(base, "charge_now");
    if (co == NULL) return smprintf("");
  }
  sscanf(co, "%d", &remcap);
  free(co);

  co = readfile(base, "status");
  if (!strncmp(co, "Discharging", 11))
  {
    status = '$';
  }
  else if (!strncmp(co, "Charging", 8))
  {
    status = '#';
  }
  else if (!strncmp(co, "Full", 4))
  {
    status = '^';
  }
  else
  {
    status = '?';
  }

  if (remcap < 0 || descap < 0) return smprintf("invalid");

  return smprintf("%.0f%[%c]", status, ((float)remcap / (float)descap) * 100);
}

char *gettemperature(char *base, char *sensor)
{
  char *co;

  co = readfile(base, sensor);
  if (co == NULL) return smprintf("");
  return smprintf("%02.0f°C", atof(co) / 1000);
}

/* -patch-suckless.org-------------------------------------------------------*/
int get_vol(void)
{
  int vol;
  snd_hctl_t *hctl;
  snd_ctl_elem_id_t *id;
  snd_ctl_elem_value_t *control;

  // To find card and subdevice: /proc/asound/, aplay -L, amixer controls
  snd_hctl_open(&hctl, "hw:0", 0);
  snd_hctl_load(hctl);

  snd_ctl_elem_id_alloca(&id);
  snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);

  // amixer controls
  snd_ctl_elem_id_set_name(id, "Master Playback Volume");

  snd_hctl_elem_t *elem = snd_hctl_find_elem(hctl, id);

  snd_ctl_elem_value_alloca(&control);
  snd_ctl_elem_value_set_id(control, id);

  snd_hctl_elem_read(elem, control);
  vol = (int)snd_ctl_elem_value_get_integer(control, 0);

  snd_hctl_close(hctl);
  return vol;
}

int parse_netdev(unsigned long long int *receivedabs,
                 unsigned long long int *sentabs)
{
  char buf[255];
  char *datastart;
  static int bufsize;
  int rval;
  FILE *devfd;
  unsigned long long int receivedacc, sentacc;

  bufsize = 255;
  devfd = fopen("/proc/net/dev", "r");
  rval = 1;

  // Ignore the first two lines of the file
  fgets(buf, bufsize, devfd);
  fgets(buf, bufsize, devfd);

  while (fgets(buf, bufsize, devfd))
  {
    if ((datastart = strstr(buf, "lo:")) == NULL)
    {
      datastart = strstr(buf, ":");

      // With thanks to the conky project at http://conky.sourceforge.net/
      sscanf(datastart + 1,
             "%llu  %*d     %*d  %*d  %*d  %*d   %*d        %*d       %llu",
             &receivedacc, &sentacc);
      *receivedabs += receivedacc;
      *sentabs += sentacc;
      rval = 0;
    }
  }

  fclose(devfd);
  return rval;
}

void calculate_speed(char *speedstr,
                     unsigned long long int newval,
                     unsigned long long int oldval)
{
  double speed;
  speed = (newval - oldval) / 1024.0;
  if (speed > 1024.0)
  {
    speed /= 1024.0;
    sprintf(speedstr, "%.3f M/s", speed);
  }
  else
  {
    sprintf(speedstr, "%.2f K/s", speed);
  }
}

char *get_netusage(unsigned long long int *rec, unsigned long long int *sent)
{
  unsigned long long int newrec, newsent;
  newrec = newsent = 0;
  char downspeedstr[15], upspeedstr[15];
  static char retstr[42];
  int retval;

  retval = parse_netdev(&newrec, &newsent);
  if (retval)
  {
    fprintf(stdout, "Error when parsing /proc/net/dev file.\n");
    exit(1);
  }

  calculate_speed(downspeedstr, newrec, *rec);
  calculate_speed(upspeedstr, newsent, *sent);

  sprintf(retstr, "[ %s  %s]", downspeedstr, upspeedstr);

  *rec = newrec;
  *sent = newsent;
  return retstr;
}

/* -patch-slstatus-----------------------------------------------------------*/
int pscanf(const char *path, const char *fmt, ...)
{
  FILE *fp;
  va_list ap;
  int n;

  if (!(fp = fopen(path, "r")))
  {
    // warn("fopen '%s':", path);
    return -1;
  }
  va_start(ap, fmt);
  n = vfscanf(fp, fmt, ap);
  va_end(ap);
  fclose(fp);

  return (n == EOF) ? -1 : n;
}

char *cpu_perc(void)
{
  static long double a[7];
  long double b[7], sum;

  memcpy(b, a, sizeof(b));
  /* cpu user nice system idle iowait irq softirq */
  if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf", &a[0], &a[1],
             &a[2], &a[3], &a[4], &a[5], &a[6]) != 7)
  {
    return smprintf("0.0");
  }
  if (b[0] == 0)
  {
    return smprintf("0.0");
  }

  sum = (b[0] + b[1] + b[2] + b[3] + b[4] + b[5] + b[6]) -
        (a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6]);

  if (sum == 0)
  {
    return smprintf("0.0");
  }

  return (smprintf("%.1f", (double)(100 *
                                    ((b[0] + b[1] + b[2] + b[5] + b[6]) -
                                     (a[0] + a[1] + a[2] + a[5] + a[6])) /
                                    sum)));
}

char *ram_used(void)
{
  uintmax_t total, free, buffers, cached;

  if (pscanf("/proc/meminfo",
             "MemTotal: %ju kB\n"
             "MemFree: %ju kB\n"
             "MemAvailable: %ju kB\n"
             "Buffers: %ju kB\n"
             "Cached: %ju kB\n",
             &total, &free, &buffers, &buffers, &cached) != 5)
  {
    return 0;
  }

  double ret = (total - free - buffers - cached) / 1024;
  if (ret > 1000)
  {
    return (smprintf("%.1lfG",
                     (total - free - buffers - cached) / (1024.0) / 1024.0));
  }
  return (smprintf("%.1lfM", (total - free - buffers - cached) / 1024.0));
}

int main(void)
{
  char *status = NULL;
  char *bat = NULL;
  char *tmlc = NULL;
  char *t0 = NULL;
  int vol = 0;
  char *cpu = NULL;
  char *mem = NULL;
  char *netstats = NULL;
  static unsigned long long int rec = 0, sent = 0;
  if (!(dpy = XOpenDisplay(NULL)))
  {
    fprintf(stderr, "dwmstatus: cannot open display.\n");
    return 1;
  }

  for (;; sleep(1))
  {
    t0 = gettemperature("/sys/devices/virtual/thermal/thermal_zone0/hwmon0",
                        "temp1_input");
    bat = getbattery("/sys/class/power_supply/BAT0");
    tmlc = mktimes("%a %F %R", tzlocal);
    vol = get_vol();
    cpu = cpu_perc();
    mem = ram_used();
    netstats = get_netusage(&rec, &sent);

    status = smprintf(" %s   %d%   %s%   %s   +%s   %s   %s  ", netstats, vol,
                      cpu, mem, t0, bat, tmlc);
    setstatus(status);

    free(t0);
    free(bat);
    free(cpu);
    free(mem);
    free(tmlc);
    free(status);
  }

  XCloseDisplay(dpy);

  return 0;
}
