#ifndef __BTC_GATTC_H__
#define __BTC_GATTC_H__

#include "btc_task.h"

typedef enum {
    BTC_GATTC_ACT_APP_REGISTER,
    BTC_GATTC_ACT_APP_UNREGISTER,
    BTC_GATTC_ACT_OPEN,
    BTC_GATTC_ACT_CLOSE,
    BTC_GATTC_ACT_CFG_MTU,
    BTC_GATTC_ACT_SEARCH_SERVICE,
    BTC_GATTC_ACT_GET_FIRST_CHAR,
    BTC_GATTC_ACT_GET_NEXT_CHAR,
    BTC_GATTC_ACT_GET_FIRST_DESCR,
    BTC_GATTC_ACT_GET_NEXT_DESCR,
    BTC_GATTC_ACT_GET_FIRST_INCL_SERVICE,
    BTC_GATTC_ACT_GET_NEXT_INCL_SERVICE,
    BTC_GATTC_ACT_READ_CHAR,
    BTC_GATTC_ACT_READ_CHAR_DESCR,
    BTC_GATTC_ACT_WRITE_CHAR,
    BTC_GATTC_ACT_WRITE_CHAR_DESCR,
    BTC_GATTC_ACT_PREPARE_WRITE,
    BTC_GATTC_ACT_EXECUTE_WRITE,
    BTC_GATTC_ACT_REG_FOR_NOTIFY,
    BTC_GATTC_ACT_UNREG_FOR_NOTIFY
} btc_gattc_act_t;

void btc_gattc_call_handler(btc_msg_t *msg);
void btc_gattc_cb_handler(btc_msg_t *msg);

#endif /* __BTC_GATTC_H__ */
