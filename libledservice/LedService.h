#include <utils/RefBase.h>
#include <utils/IInterface.h>
#include <utils/Parcel.h>

namespace android {

class ILedService : public IInterface
{
public:
   enum {
        CONNECT = IBinder::FIRST_CALL_TRANSACTION,
        LED_ON 
   };

public:
    /*
      #define DECLARE_META_INTERFACE(INTERFACE)                           \
      static const String16 descriptor;                                   \
      static sp<I##INTERFACE> asInterface(const sp<IBinder>& obj);        \
      virtual String16 getInterfaceDescriptor() const;                    \
     */
    DECLARE_META_INTERFACE(LedService);

    int setOn(int led);
};


class BnLedService: public BnInterface<ILedService>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

class LedService : public BnLedService
{
public:
    static void instantiate();
    virtual int setOn(int led);

private:
    LedService();
    virtual ~LedService();
};   
 
}   
