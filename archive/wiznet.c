/**
 * As usual, all I ask is that you e-mail me letting me know that you're using this.
 * This code uses Lope's color codes, so if you don't have them, just take out all the
 * {R, {V, and {x 's that you see.  Just subsitute this for the original do_wiznet in your
 * act_wiz.c file.  This is just a modified version of the original do_wiznet, borrowing from
 * the do_channel code as well.  Much nicer to  use, IMHO.<G>
 * If you get some improvements to it, be sure to let me know.<G>
 * charasan@gmail.com
 */

void do_wiznet( CHAR_DATA *ch, char *argument )
{
   int flag;
   char buf[MAX_STRING_LENGTH];
                
   if ( argument[0] == '\0' )
/* Show wiznet options - just like channel command */
   {
        send_to_char("{VWELCOME TO WIZNET!!!\n\r", ch);
        send_to_char("   Option      Status\n\r",ch);
        send_to_char("---------------------\n\r",ch);
        /* list of all wiznet options */
        buf[0] = '\0';
        
        for (flag = 0; wiznet_table[flag].name != NULL; flag++)
        {
            if (wiznet_table[flag].level <= get_trust(ch))
            {
                sprintf( buf, "%-14s %s\t", wiznet_table[flag].name,
IS_SET(ch->wiznet,wiznet_table[flag].flag) ? "{RON{V" : "OFF" );
                send_to_char(buf, ch);   
                col++;
                if (col==3)
                {
                  send_to_char("\n\r",ch);
                  col=0;
                }
            }
        }
/* To avoid color bleeding */
     send_to_char("{x",ch);
     return;
   }    
 
   if (!str_prefix(argument,"on"))
   {     
        send_to_char("{VWelcome to Wiznet!{x\n\r",ch);
        SET_BIT(ch->wiznet,WIZ_ON);
        return;
   }
                
   if (!str_prefix(argument,"off"))
   {
        send_to_char("{VSigning off of Wiznet.{x\n\r",ch);
        REMOVE_BIT(ch->wiznet,WIZ_ON);
        return;
   }
        
   flag = wiznet_lookup(argument);
        
   if (flag == -1 || get_trust(ch) < wiznet_table[flag].level) 
   {
        send_to_char("{VNo such option.{x\n\r",ch);
        return;
   }

   if (IS_SET(ch->wiznet,wiznet_table[flag].flag))
   {
        sprintf(buf,"{VYou will no longer see %s on wiznet.{x\n\r",
                wiznet_table[flag].name);
        send_to_char(buf,ch);
        REMOVE_BIT(ch->wiznet,wiznet_table[flag].flag);
        return;
   }
   else  
   {
        sprintf(buf,"{VYou will now see %s on wiznet.{x\n\r",
                wiznet_table[flag].name);
        send_to_char(buf,ch);
        SET_BIT(ch->wiznet,wiznet_table[flag].flag);
        return;
   }
}

