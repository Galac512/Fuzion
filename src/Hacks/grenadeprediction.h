#pragma once
#include "../Hooks/hooks.h"

#include "../SDK/CViewRender.h"
#include "../SDK/IInputSystem.h"

namespace GrenadePrediction
{
<<<<<<< HEAD
        extern float cameraHeight;
        // Hooks
        void OverrideView( CViewSetup* pSetup );
        void Paint();
        void RenderView( void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw );
        void CreateMove( CUserCmd *cmd ); // For not allowing Jumps via Scroll wheel
}
=======
    extern float cameraHeight;
    // Hooks
    void OverrideView( CViewSetup* pSetup );
    void Paint();
    void RenderView( void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw );
    void CreateMove( CUserCmd *cmd ); // For not allowing Jumps via Scroll wheel
}
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
