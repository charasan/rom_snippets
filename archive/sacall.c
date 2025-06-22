/* Yet another snippet by Charasan
 * All I ask is you e-mail me at charasan@gmail.com and let me know
 * that you're using it.  Thanks and enjoy!
 */
 
// Stick this piece of code in your do_sacrifice right below the shown line and recompile!

// Right below the lines that read :

        send_to_char(
            "Mota appreciates your offer and may accept it later.\n\r", ch );
        return;
    }
    
// --------------------------------------------------------------------------------------------------------

// Place this piece of code.  Simple as that! <G>

        if (!str_cmp("all",arg) || !str_prefix("all.",arg))
        {
                OBJ_DATA *obj_next;
                bool found = FALSE;
      
                for (obj = ch->in_room->contents;obj;obj = obj_next)
                { 
                        obj_next = obj->next_content;

                        if (arg[3] != '\0' && !is_name(&arg[4],obj->name))
                                continue;

                        if (  (!CAN_WEAR(obj,ITEM_TAKE) || CAN_WEAR(obj,ITEM_NO_SAC))
                                || (obj->item_type == ITEM_CORPSE_PC && obj->contains))
                                continue;
                        silver = UMAX(1,obj->level * 3);
        
        if (obj->item_type != ITEM_CORPSE_NPC && obj->item_type != ITEM_CORPSE_PC)
                        silver = UMIN(silver,obj->cost);
            
                        found = TRUE;
                        printf_to_char( ch, "{cMota gives you {Y%d{c silver for your sacrifice of {w%s{c.{x\n\r", silver, obj->short_descr );
                        act( "$n sacrifices $p to Mota.", ch, obj, NULL, TO_ROOM );
                        ch->silver += silver;
                        extract_obj( obj );

                        if (IS_SET(ch->act,PLR_AUTOSPLIT))
                        { 
                                members = 0;
                                for (gch = ch->in_room->people;gch;gch = gch->next_in_room)
                                        if (is_same_group(ch,gch))
                                                members++;
                                if (members > 1 && silver > 1)
                                { 
                                        sprintf(buf,"%d",silver);
                                        do_function( ch, &do_split, buf); 
                                }
                        }
                }
                if (found)
                        wiznet("$N sends up everything in that room as a burnt offering.",ch,obj,WIZ_SACCING,0,0);
        
                else
                        send_to_char("There is nothing sacrificable in this room.\n\r",ch);
                        return;
        }



// ALL THERE IS TO IT! <G>
