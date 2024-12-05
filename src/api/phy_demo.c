#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/mii.h>
#include <linux/sockios.h>
#include <sys/types.h>
#include <sys/socket.h>

int read_phy_reg(int fd, struct ifreq *ifr, int reg_num, uint16_t *val)
{
    struct mii_ioctl_data *mii = (struct mii_ioctl_data *)&ifr->ifr_data;
    mii->reg_num = reg_num;
    if ( ioctl(fd, SIOCGMIIREG, ifr ) < 0)
    {
        perror("ioctl SIOCFMIIREG");
        return -1;
    }
    *val = mii->val_out;
    return 0;
}

int write_phy_reg(int fd, struct ifreq *ifr, int reg_num, uint16_t val)
{
    struct mii_ioctl_data *mii = (struct mii_ioctl_data *)&ifr->ifr_data;
    mii->reg_num = reg_num;
    mii->val_in = val;
    if (ioctl(fd, SIOCSMIIREG, ifr) < 0)
    {
        perror("ioctl SIOCSMIIREG");
        return -1;
    }
    return 0;
}

int main()
{
    const char *iface = "eth0";
    int fd;
    struct ifreq ifr;
    uint16_t val;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return EXIT_FAILURE;
    }

    strncpy(ifr.ifr_name, iface, IF_NAMESIZE - 1);
    ifr.ifr_data = (void* )malloc(sizeof(struct mii_ioctl_data));
    if ( !ifr.ifr_data  )
    {
        perror("malloc");
        close(fd);
        return EXIT_FAILURE;
    }

    if (ioctl(fd, SIOCGMIIPHY, &ifr) < 0)
    {
        perror("ioctl SIOCGMIIPHY");
        free(ifr.ifr_data);
        close(fd);
        return EXIT_FAILURE;
    }

    if (read_phy_reg(fd, &ifr, MII_BMCR, &val) == 0)
    {
        printf("PHY Control Register (0): 0x%04x\n",val);
    }

    uint16_t new_val = val | BMCR_RESET;
    if (write_phy_reg(fd, &ifr, MII_BMCR, new_val) == 0)
    {
        printf("PHY Control Register (0) updated to: 0x%04x\n",new_val);
    }

    free(ifr.ifr_data);
    close(fd);
    return EXIT_SUCCESS;
}