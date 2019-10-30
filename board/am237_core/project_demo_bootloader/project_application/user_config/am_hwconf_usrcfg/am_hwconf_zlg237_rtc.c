/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG117 RTC �û������ļ�
 * \sa am_hwconf_zlg237_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-23  zp, first implementation
 * \endinternal
 */

#include "am_zlg237.h"
#include "am_zlg237_inst_init.h"
#include "am_zlg237_rtc.h"
#include "amhw_zlg237_pwr.h"
#include "amhw_zlg237_rcc.h"
#include "zlg237_periph_map.h"
#include "ametal.h"
#include "am_delay.h"


#define RTC_CLK_SOUR  AMHW_ZLG237_RTCCLK_HSE_DIV128
/**
 * \addtogroup am_if_src_hwconf_zlg237_rtc
 * \copydoc am_hwconf_zlg237_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __zlg237_plfm_rtc_init()
{
    amhw_zlg237_rcc_apb1_enable(AMHW_ZLG237_RCC_APB1_PWR); /* ʹ�ܵ�Դʱ�� */
    amhw_zlg237_rcc_apb1_enable(AMHW_ZLG237_RCC_APB1_BKP); /* ʹ�ܱ���ʱ�� */
    amhw_zlg237_pwr_bkp_access_enable(ZLG237_PWR,1);       /* ȡ���������д���� */
    amhw_zlg237_rcc_bdcr_bdrst_reset();                    /* ��������������λ */
    am_udelay(5);
    amhw_zlg237_rcc_bdcr_bdrst_reset_end();                /* ������������λ���� */

    /* RTC ʱ��Դѡ��Ϊ�ⲿRTCʱ��Դ */
    amhw_zlg237_rcc_bdcr_rtc_clk_set((amhw_zlg237_rtc_clk_src)RTC_CLK_SOUR);
    am_mdelay(1);
    amhw_zlg237_rcc_bdcr_rtc_enable();                     /* RTCʱ��ʹ�� */

}

/** ��� RTC ƽ̨��ʼ�� */
void __zlg237_plfm_rtc_deinit(void)
{
    amhw_zlg237_rcc_apb1_disable(AMHW_ZLG237_RCC_APB1_PWR); /* ���ܵ�Դʱ�� */
    amhw_zlg237_rcc_apb1_disable(AMHW_ZLG237_RCC_APB1_BKP); /* ���ܱ���ʱ�� */
    amhw_zlg237_pwr_bkp_access_enable(ZLG237_PWR,0);        /* �������д���� */
    amhw_zlg237_rcc_bdcr_rtc_disable();                     /* RTCʱ�ӽ��� */
}

/** \brief RTC�豸��Ϣ */
const struct am_zlg237_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    ZLG237_RTC_BASE,

    /** \brief ��Դ����PWR����ַ */
    ZLG237_PWR_BASE,

    /** \brief ���ݿ���BKP����ַ */
    ZLG237_BKP_BASE,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    /** \brief RTC�豸ʱ��Դ */
    RTC_CLK_SOUR,

    /** \brief ƽ̨��ʼ������ */
    __zlg237_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __zlg237_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_zlg237_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_zlg237_rtc_inst_init (void)
{
    return am_zlg237_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_zlg237_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_zlg237_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */