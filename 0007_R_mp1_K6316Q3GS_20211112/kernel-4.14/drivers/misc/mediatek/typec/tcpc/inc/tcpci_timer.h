/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef TCPC_TIMER_H_INCLUDED
#define TCPC_TIMER_H_INCLUDED

#include <linux/kernel.h>
#include "tcpci_config.h"

struct tcpc_device;
enum {
#ifdef CONFIG_USB_POWER_DELIVERY
	PD_TIMER_DISCOVER_ID = 0,
	PD_TIMER_BIST_CONT_MODE,
	PD_TIMER_HARD_RESET_COMPLETE,
	PD_TIMER_NO_RESPONSE,
	PD_TIMER_PS_HARD_RESET,
	PD_TIMER_PS_SOURCE_OFF,
	PD_TIMER_PS_SOURCE_ON,
	PD_TIMER_PS_TRANSITION,
	PD_TIMER_SENDER_RESPONSE,
	PD_TIMER_SINK_ACTIVITY,
	PD_TIMER_SINK_REQUEST,
	PD_TIMER_SINK_WAIT_CAP,
	PD_TIMER_SOURCE_ACTIVITY,
	PD_TIMER_SOURCE_CAPABILITY,
	PD_TIMER_SOURCE_START,
	PD_TIMER_VCONN_ON,
#ifdef CONFIG_USB_PD_VCONN_STABLE_DELAY
	PD_TIMER_VCONN_STABLE,
#endif	/* CONFIG_USB_PD_VCONN_STABLE_DELAY */
	PD_TIMER_VDM_MODE_ENTRY,
	PD_TIMER_VDM_MODE_EXIT,
	PD_TIMER_VDM_RESPONSE,
	PD_TIMER_SOURCE_TRANSITION,
	PD_TIMER_SRC_RECOVER,
#ifdef CONFIG_USB_PD_REV30
	PD_TIMER_CK_NO_SUPPORT,
#ifdef CONFIG_USB_PD_REV30_COLLISION_AVOID
	PD_TIMER_SINK_TX,
#endif	/* CONFIG_USB_PD_REV30_COLLISION_AVOID */
#ifdef CONFIG_USB_PD_REV30_PPS_SOURCE
	PD_TIMER_SOURCE_PPS_TIMEOUT,
#endif	/* CONFIG_USB_PD_REV30_PPS_SOURCE */
#endif	/* CONFIG_USB_PD_REV30 */

/* PD_TIMER (out of spec )*/
	PD_TIMER_VSAFE0V_DELAY,
	PD_TIMER_VSAFE0V_TOUT,
	PD_TIMER_DISCARD,
	PD_TIMER_VBUS_STABLE,
	PD_TIMER_VBUS_PRESENT,
	PD_TIMER_UVDM_RESPONSE,
	PD_TIMER_DFP_FLOW_DELAY,
	PD_TIMER_UFP_FLOW_DELAY,
	PD_TIMER_VCONN_READY,
	PD_PE_VDM_POSTPONE,

#ifdef CONFIG_USB_PD_REV30
#ifdef CONFIG_USB_PD_REV30_COLLISION_AVOID
	PD_TIMER_DEFERRED_EVT,
#ifdef CONFIG_USB_PD_REV30_SNK_FLOW_DELAY_STARTUP
	PD_TIMER_SNK_FLOW_DELAY,
#endif	/* CONFIG_USB_PD_REV30_SNK_FLOW_DELAY_STARTUP */
#endif	/* CONFIG_USB_PD_REV30_COLLISION_AVOID */
#endif	/* CONFIG_USB_PD_REV30 */

	PD_TIMER_PE_IDLE_TOUT,
	PD_PE_TIMER_END_ID,
#endif /* CONFIG_USB_POWER_DELIVERY */

/* TYPEC_RT_TIMER (out of spec )*/
#ifdef CONFIG_USB_POWER_DELIVERY
	TYPEC_RT_TIMER_START_ID = PD_PE_TIMER_END_ID,
#else
	TYPEC_RT_TIMER_START_ID = 0,
#endif	/* CONFIG_USB_POWER_DELIVERY */

	TYPEC_RT_TIMER_SAFE0V_DELAY = TYPEC_RT_TIMER_START_ID,
	TYPEC_RT_TIMER_SAFE0V_TOUT,
	TYPEC_RT_TIMER_ROLE_SWAP_START,
	TYPEC_RT_TIMER_ROLE_SWAP_STOP,
	TYPEC_RT_TIMER_STATE_CHANGE,
	TYPEC_RT_TIMER_NOT_LEGACY,
	TYPEC_RT_TIMER_LEGACY_STABLE,
	TYPEC_RT_TIMER_LEGACY_RECYCLE,
	TYPEC_RT_TIMER_AUTO_DISCHARGE,
	TYPEC_RT_TIMER_LOW_POWER_MODE,

#ifdef CONFIG_USB_POWER_DELIVERY
	TYPEC_RT_TIMER_PE_IDLE,
/*prize add by sunshuai for A-C 30w charge 20201109-start */
#ifdef CONFIG_PRIZE_ATOC_TYPEC_CHARGE
#ifdef CONFIG_TYPEC_WAIT_BC12
	TYPEC_RT_TIMER_SINK_WAIT_BC12,
#endif /* CONFIG_TYPEC_WAIT_BC12 */
#endif/* CONFIG_PRIZE_ATOC_TYPEC_CHARGE */
/*prize add by sunshuai for A-C 30w charge 20201109-end */
#endif	/* CONFIG_USB_POWER_DELIVERY */
	TYPEC_TIMER_ERROR_RECOVERY,
/* TYPEC-TRY-TIMER */
	TYPEC_TRY_TIMER_START_ID,
	TYPEC_TRY_TIMER_DRP_TRY = TYPEC_TRY_TIMER_START_ID,
	TYPEC_TRY_TIMER_DRP_TRYWAIT,
/* TYPEC-DEBOUNCE-TIMER */
	TYPEC_TIMER_START_ID,
	TYPEC_TIMER_CCDEBOUNCE = TYPEC_TIMER_START_ID,
	TYPEC_TIMER_PDDEBOUNCE,
#ifdef CONFIG_COMPATIBLE_APPLE_TA
	TYPEC_TIMER_APPLE_CC_OPEN,
#endif /* CONFIG_COMPATIBLE_APPLE_TA */
	TYPEC_TIMER_TRYCCDEBOUNCE,
	TYPEC_TIMER_SRCDISCONNECT,
	TYPEC_TIMER_DRP_SRC_TOGGLE,
#ifdef CONFIG_TYPEC_CAP_NORP_SRC
	TYPEC_TIMER_NORP_SRC,
#endif	/* CONFIG_TYPEC_CAP_NORP_SRC */
//prize add by huarui, cc controller sgm7220, start
#ifdef CONFIG_TCPC_SGM7220
	TYPEC_TIMER_VBUS_CHECK,
#endif	/* CONFIG_TCPC_SGM7220 */
//prize add by huarui, cc controller sgm7220, end
	PD_TIMER_NR,
};

extern int tcpci_timer_init(struct tcpc_device *tcpc);
extern int tcpci_timer_deinit(struct tcpc_device *tcpc);
extern void tcpc_restart_timer(struct tcpc_device *tcpc, uint32_t timer_id);
extern void tcpc_enable_timer(struct tcpc_device *tcpc, uint32_t timer_id);
extern void tcpc_enable_wakeup_timer(struct tcpc_device *tcpc, bool en);
extern void tcpc_disable_timer(
		struct tcpc_device *tcpc, uint32_t timer_id);
extern void tcpc_reset_typec_try_timer(struct tcpc_device *tcpc);
extern void tcpc_reset_typec_debounce_timer(struct tcpc_device *tcpc);

extern void tcpc_reset_pe_timer(struct tcpc_device *tcpc);
#endif /* TCPC_TIMER_H_INCLUDED */