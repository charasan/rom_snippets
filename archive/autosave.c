/**
 * This is an early version of my OLC Autosave.  What this does is allow area flagged CHANGED to automatically
 * save themselves without asave changed being typed.  I've seen so many good changes get lost due to builders
 * forgetting to do this.  All i ask is that you email me at charasan@gmail.com and let me know you're using it.
 * Thanks.
 */

// in update.c:
// In local functions, add this at the bottom :
void    olcautosave     args( ( void ) );

// in the update_handler, add this :
   in if ( --pulse_area     <= 0 )
// add :
        olcautosave     ( );
// Then, somewhere near the bottom add this code :

void olcautosave( void )
{
   AREA_DATA *pArea;
   DESCRIPTOR_DATA *d;
   char buf[MAX_INPUT_LENGTH];

/*  if you're still adding areas manually, you may need to remove the next line - Chance */                
        save_area_list();
        for ( d = descriptor_list; d != NULL; d = d->next )
        {
           if ( d->editor)
                   send_to_char( "OLC Autosaving:\n\r", d->character );
        }
        sprintf( buf, "None.\n\r" );
                 
        for( pArea = area_first; pArea; pArea = pArea->next ) 
        {
            /* Save changed areas. */
            if ( IS_SET(pArea->area_flags, AREA_CHANGED) )
            {
                save_area( pArea );
                sprintf( buf, "%24s - '%s'", pArea->name, pArea->file_name );
                for ( d = descriptor_list; d != NULL; d = d->next )
                {
                   if ( d->editor )
                   {
                        send_to_char( buf, d->character );
                        send_to_char( "\n\r", d->character );
                   }
                }   
                REMOVE_BIT( pArea->area_flags, AREA_CHANGED );
            }
        }       
        
        if ( !str_cmp( buf, "None.\n\r" ) )
        {
           for ( d = descriptor_list; d != NULL; d = d->next )
           {
                if ( d->editor )
                        send_to_char( buf, d->character );
           }     
        }
         
        return;
}

