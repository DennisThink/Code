using System;
using System.Collections.Generic;
using RimWorld;
using Verse;
using System.Linq;
using UnityEngine;
namespace SmartClean
{
    public class SmartCleanMainMenu : Window
    {
        public const float WinWidth = 200;
        public ArchitectCategoryTab selectedDesPanel;

        public SmartCleanMainMenu() {
            windowRect.xMin = 0;
            windowRect.xMax = 100;
            windowRect.yMin = 100;
            windowRect.yMax = 200;
        }

        public override void DoWindowContents(Rect inRect)
        {
            FloatMenu menu = AddFloatMenu();
            if(null != menu)
            {
                Find.WindowStack.Add(menu);
            }
        }

        public FloatMenu AddFloatMenu()
        {
            List<FloatMenuOption> menuList = new List<FloatMenuOption>();
            FloatMenuOption aboutMenu = new FloatMenuOption("About", delegate ()
            {
                SmartCleanMainMenu.OnAbout();
            },MenuOptionPriority.Default, null, null, 0f, null, null, true, 0);
            menuList.Add(aboutMenu);

            return new FloatMenu(menuList);
        }
        public override void OnAcceptKeyPressed()
        {
            Log.Warning("SmartClean OnAcceptKeyPressed");
            if (null != this)
            {
                Rect pos = this.windowRect;
                string str = string.Format(" DoWindowContents Smart Clean DoWindowContents {0} {1} {2} {3}", pos.xMin, pos.yMin, pos.xMax, pos.yMax);
                Log.Warning(str);
            }
            base.OnAcceptKeyPressed();
        }

        public override void OnCancelKeyPressed()
        {
            Log.Warning("SmartClean OnCancelKeyPressed");
            if (null != this)
            {
                Rect pos = this.windowRect;
                string str = string.Format(" DoWindowContents Smart Clean DoWindowContents {0} {1} {2} {3}", pos.xMin, pos.yMin, pos.xMax, pos.yMax);
                Log.Warning(str);
            }
            base.OnCancelKeyPressed();
        }

        public static void OnAbout()
        {
            Log.TryOpenLogWindow();
            Log.Warning("This is Writen By Dennis Mi");
        }

        public static void OnReportBug()
        {
            Log.TryOpenLogWindow();
            Log.Warning("This is Writen By Dennis Mi,Report Bug to DennisThink");
        }
    }
}
