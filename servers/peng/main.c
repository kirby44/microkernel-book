#include <libs/common/print.h>
#include <libs/user/ipc.h>
#include <libs/user/syscall.h>

void main(void) {
    // pengサーバとして登録する
    ASSERT_OK(ipc_register("peng"));
    TRACE("ready");

    // メインループ
    while (true) {
        struct message m;
        ASSERT_OK(ipc_recv(IPC_ANY, &m));
        switch (m.type) {
            case PENG_MSG: {
                DBG("received peng message from #%d (value=%d)", m.src,
                    m.peng.value);

                m.type = PENG_REPLY_MSG;
                m.peng_reply.value = 42;
                ipc_reply(m.src, &m);
                break;
            }
            default:
                WARN("unhandled message: %s (%x)", msgtype2str(m.type), m.type);
                break;
        }
    }
}
