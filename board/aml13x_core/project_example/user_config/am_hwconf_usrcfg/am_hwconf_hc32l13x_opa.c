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
 * \brief HC32 OPA �û������ļ�
 * \sa am_hwconf_hc32_opa.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-27
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_hc32.h"
#include "am_hc32_opa.h"
#include "hw/amhw_hc32_opa.h"
#include "hc32_pin.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_opa
 * \copydoc am_hwconf_hc32_opa.c
 * @{
 */

/**
 * \brief OPA ƽ̨��ʼ��
 */
void __hc32_plfm_opa_init (void)
{
    /* ����OPAʱ�� */
    am_clk_enable (CLK_OPA);

    /* ����BGRʱ�� */
    am_clk_enable (CLK_ADC_BGR);

    /* PB00 OPA���� */
    am_gpio_pin_cfg (PIOB_0, PIOB_0_AIN);
}

/**
 * \brief OPA ƽ̨ȥ��ʼ��
 */
void __hc32_plfm_opa_deinit (void)
{
    /* �ر�OPAʱ�� */
    am_clk_disable (CLK_OPA);

    /* �ر�BGRʱ�� */
    am_clk_disable (CLK_ADC_BGR);
}

/** \brief OPA �豸��Ϣ */
static const am_hc32_opa_devinfo_t __g_opa_devinfo =
{
    /**< \brief ָ��OPA�Ĵ������ָ�� */
    HC32_OPA_BASE,

    /**
     *  \brief OPA�Զ�У׼�������û�����ֵ�ο�ö�٣��Զ�У׼�����������
     *
     *  \note :����У׼ʱ��10us
     */
    AMHW_HC32_OPA_CLK_16,

    /**
     * \brief OPAУ׼��ʽ,�ο��궨�壺OPA �Զ�У��ѡ������
     */
    AMHW_HC32_OPA_AZ_SW,

    /**
     * \brief OPA����ģʽ ,�ο�am_hc32_opa.h�궨�壺OPA����ģʽѡ��
     */
    AM_HC32_OPA_GENERAL,

    /**< \brief LVDƽ̨��ʼ������ */
    __hc32_plfm_opa_init,

    /**< \brief LVDƽ̨���ʼ������  */
    __hc32_plfm_opa_deinit,
};

/** \brief OPA�豸ʵ�� */
static am_hc32_opa_dev_t __g_opa_dev;

/** \brief OPA ʵ����ʼ�������OPA��׼������ */
am_opa_handle_t am_hc32_opa_inst_init (void)
{
    return am_hc32_opa_init(&__g_opa_dev, &__g_opa_devinfo);
}

/** \brief OPA ʵ�����ʼ�� */
void am_hc32_opa_inst_deinit (am_opa_handle_t handle)
{
    am_hc32_opa_deinit(handle);
}

/**
 * @}
 */

/* end of file */