//////////////////////////////////////////////////////////////////////////////
// Lynx 3wire EEPROM class header file                                      //
//////////////////////////////////////////////////////////////////////////////


#ifndef EEPROM_H
#define EEPROM_H

enum {EE_NONE=0, EE_START, EE_DATA, EE_BUSY, EE_WAIT};

class CEEPROM : public CLynxBase
{

  
#define min(x,y) x>y?y:x

public:
   CEEPROM();
   ~CEEPROM();

   void	Reset(void);

   bool Available(void){ return type!=0;};
   void ProcessEepromIO(UBYTE iodir,UBYTE iodat);
   void ProcessEepromCounter(UWORD cnt);
   void ProcessEepromBusy(void);
   bool OutputBit(void)
   {
      return mAUDIN_ext;
   };
   void SetEEPROMType(UBYTE b);
   int Size(void);
   int InitFrom(char *data,int count){ memcpy(romdata,data,min(count,Size()));};

   void	Poke(ULONG addr,UBYTE data) { };
   UBYTE	Peek(ULONG addr)
   {
      return(0);
   };

   void SetFilename(char* f){strcpy(filename,f);};
   char* GetFilename(void){ return filename;};
   
   void Load(void);
   void Save(void);

private:
    char filename[1024];
    
   void UpdateEeprom(UWORD cnt);
   UBYTE type; // 0 ... no eeprom

   UWORD ADDR_MASK;
   UBYTE CMD_BITS;
   UBYTE ADDR_BITS;
   ULONG DONE_MASK;

   UBYTE iodir, iodat;
   UWORD counter;
   int busy_count;
   int state;
   UWORD readdata;

   ULONG data;
   UWORD romdata[1024];// 128, 256, 512, 1024 WORDS bzw 128 bytes fuer byte zugriff
   UWORD addr;
   int sendbits;
   bool readonly;

   bool mAUDIN_ext;// OUTPUT

public:
};

#endif
