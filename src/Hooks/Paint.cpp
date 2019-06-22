#include "hooks.h"

#include "../interfaces.h"
#include "../settings.h"
#include "../Utils/draw.h"
#include "../fonts.h"

#include "../Hacks/esp.h"
#include "../Hacks/dlights.h"
#include "../Hacks/grenadehelper.h"
#include "../Hacks/grenadeprediction.h"
#include "../Hacks/recoilcrosshair.h"
#include "../Hacks/hitmarkers.h"
#include "../Hacks/eventlog.h"
#include "../Hacks/snipercrosshair.h"
#include "../Hacks/angleindicator.h"
#include "../Hacks/watermark.h"

#include "../glhook.h"

#include <mutex>

extern StartDrawingFn StartDrawing;
extern FinishDrawingFn FinishDrawing;

int Paint::engineWidth;
int Paint::engineHeight;

std::mutex drawMutex;


typedef void (*PaintFn) (void*, PaintMode_t);

void Hooks::Paint(void* thisptr, PaintMode_t mode)
{
        engineVGuiVMT->GetOriginalMethod<PaintFn>(15)(thisptr, mode);

        if (Settings::ScreenshotCleaner::enabled && engine->IsTakingScreenshot())
                return;

        if (mode & PAINT_UIPANELS)
        {
                int prevRecords = Draw::drawRequests.size(); // # of requests from last call

<<<<<<< HEAD
                ESP::PaintToUpdateMatrix(); // Just for updating the viewMatrix
                /* These functions make drawRequests */
                Dlights::Paint();
                ESP::Paint();
                GrenadeHelper::Paint();
                Recoilcrosshair::Paint();
                Hitmarkers::Paint();
                SniperCrosshair::Paint();
                AngleIndicator::Paint();
                GrenadePrediction::Paint();
                Watermark::Paint();
=======
    int width, height;
    engine->GetScreenSize( width, height );

	if (Settings::ScreenshotCleaner::enabled && engine->IsTakingScreenshot())
		return;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

                if( Settings::ESP::backend == DrawingBackend::SURFACE ){
                        StartDrawing(surface);
                        for( long unsigned int i = 0; i < Draw::drawRequests.size(); i++ ){
#define value Draw::drawRequests[i]
                                switch( value.type ){
                                case DRAW_LINE:
                                        Draw::Line( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_RECT:
                                        Draw::Rectangle( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_RECT_FILLED:
                                        Draw::FilledRectangle( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_CIRCLE:
                                        Draw::Circle( Vector2D( value.x0, value.y0 ), value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_CIRCLE_FILLED:
                                        Draw::FilledCircle( Vector2D( value.x0, value.y0 ), value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_CIRCLE_3D:
                                        Draw::Circle3D( value.pos, value.circleSegments, value.circleRadius, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_TEXT:
                                        Draw::Text( value.x0, value.y0, value.text, esp_font, Color::FromImColor( value.color ) );
                                        break;
                                case DRAW_ITEM_TEXT:
                                        Draw::Text( value.x0, value.y0, value.text, esp_font, Color::FromImColor( value.color ) );
                                        break;
                                }
#undef value
                        }
                        FinishDrawing(surface);
                }
                std::unique_lock<std::mutex> lock( drawMutex );
                Draw::drawRequests.erase( Draw::drawRequests.begin( ), Draw::drawRequests.begin( ) + prevRecords );
        }
}

void Hooks::PaintImGui()
{
        if( Settings::ESP::backend != DrawingBackend::IMGUI )
                return;

<<<<<<< HEAD
        std::unique_lock<std::mutex> lock( drawMutex );

        for( long unsigned int i = 0; i < Draw::drawRequests.size(); i++ ){
#define value Draw::drawRequests[i]
                switch( value.type )
                {
                case DRAW_LINE:
                        Draw::ImLine( ImVec2( value.x0, value.y0 ), ImVec2( value.x1, value.y1 ), value.color );
                        break;
                case DRAW_RECT:
                        Draw::ImRect( value.x0, value.y0, value.x1, value.y1, value.color );
=======
        ESP::PaintToUpdateMatrix(); // Just for updating the viewMatrix
        /* These functions make drawRequests */
        Dlights::Paint();
        ESP::Paint();
        GrenadeHelper::Paint();
        Recoilcrosshair::Paint();
        Hitmarkers::Paint();
        Eventlog::Paint();        
        SniperCrosshair::Paint();
        AngleIndicator::Paint();
        GrenadePrediction::Paint();

        if( Settings::ESP::backend == DrawingBackend::SURFACE ){
            StartDrawing(surface);
            for( const DrawRequest &value : Draw::drawRequests ){
                switch( value.type ){
                    case DRAW_LINE:
                        Draw::Line( value.x0, value.y0, value.x1, value.y1, Color::FromImColor( value.color ) );
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
                        break;
                case DRAW_RECT_FILLED:
                        Draw::ImRectFilled( value.x0, value.y0, value.x1, value.y1, value.color );
                        break;
                case DRAW_CIRCLE:
                        Draw::ImCircle( ImVec2( value.x0, value.y0 ), value.color, value.circleRadius, value.circleSegments, value.thickness );
                        break;
                case DRAW_CIRCLE_FILLED:
                        Draw::ImCircleFilled( ImVec2( value.x0, value.y0 ), value.color, value.circleRadius, value.circleSegments );
                        break;
                case DRAW_CIRCLE_3D:
                        Draw::ImCircle3D( value.pos, value.circleSegments, value.circleRadius, value.color );
                        break;
                case DRAW_TEXT:
                        Draw::ImText( ImVec2( value.x0, value.y0 ), value.color, value.text, nullptr, 0.0f, nullptr, value.fontflags );
                        break;
                case DRAW_ITEM_TEXT:
                        Draw::ImText( ImVec2( value.x0, value.y0 ), value.color, value.text, nullptr, 0.0f, nullptr, value.fontflags, ImGui::weaponFont );
                        break;
#undef value
                }
        }
<<<<<<< HEAD
}
=======
        std::unique_lock<std::mutex> lock( drawMutex );
        if( Paint::engineWidth != width || Paint::engineHeight != height ){
            Paint::engineWidth = width;
            Paint::engineHeight = height;
        }
        Draw::drawRequests.erase( Draw::drawRequests.begin( ), Draw::drawRequests.begin( ) + prevRecords );
    }
}

void Hooks::PaintImGui()
{
	if( Settings::ESP::backend != DrawingBackend::IMGUI )
        return;

    std::unique_lock<std::mutex> lock( drawMutex );

    float width = (float)Paint::engineWidth;
    float height = (float)Paint::engineHeight;
    float imWidth = ImGui::GetWindowWidth();
    float imHeight = ImGui::GetWindowHeight();

    for( const DrawRequest &value : Draw::drawRequests ){
        /* Convert in case there are stretched resolution users - DONT write to original struct! */
        int x0 = (int)((value.x0 / width) * imWidth);
        int y0 = (int)((value.y0 / height) * imHeight);
        int x1 = (int)((value.x1 / width) * imWidth);
        int y1 = (int)((value.y1 / height) * imHeight);

        switch( value.type ){
            case DRAW_LINE:
                Draw::ImLine( ImVec2( x0, y0 ), ImVec2( x1, y1 ), value.color );
                break;
            case DRAW_RECT:
                Draw::ImRect( x0, y0, x1, y1, value.color );
                break;
            case DRAW_RECT_FILLED:
                Draw::ImRectFilled( x0, y0, x1, y1, value.color );
                break;
            case DRAW_CIRCLE:
                Draw::ImCircle( ImVec2( x0, y0 ), value.color, value.circleRadius, value.circleSegments, value.thickness );
                break;
            case DRAW_CIRCLE_FILLED:
                Draw::ImCircleFilled( ImVec2( x0, y0 ), value.color, value.circleRadius, value.circleSegments );
                break;
            case DRAW_CIRCLE_3D:
                Draw::ImCircle3D( value.pos, value.circleSegments, value.circleRadius, value.color );
                break;
            case DRAW_TEXT:
                Draw::ImText( ImVec2( x0, y0 ), value.color, value.text, nullptr, 0.0f, nullptr, value.fontflags );
                break;
        }
    }
}
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
