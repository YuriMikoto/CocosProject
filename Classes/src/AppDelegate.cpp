#include "AppDelegate.h"
#include "MainMenuScene.h"

USING_NS_CC;

typedef struct tagResource 
{ 
	cocos2d::Size size; char directory[100]; 
} 

Resource; // Landscape config. 
// 800x480 = Normal screen, WVGA 
static Resource smallResolution = { cocos2d::Size(800, 480), "sd" }; 
// 1280x800 = Extra large screen, WXGA, medium density screen (160) 
static Resource mediumResolution = { cocos2d::Size(1280, 800), "hd" }; 
// 1900x1200 = WUXGA, Devices with such as Nexus 7, Nvidia Shield. 
static Resource largeResolution = { cocos2d::Size(1920, 1200), "shd" }; 
static cocos2d::Size designResolutionSize = mediumResolution.size;

/*static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);*/

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MyCppGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("MyCppGame");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolution.size.height)
    {        
        director->setContentScaleFactor(MIN(largeResolution.size.height/designResolutionSize.height, largeResolution.size.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolution.size.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolution.size.height/designResolutionSize.height, mediumResolution.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolution.size.height/designResolutionSize.height, smallResolution.size.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;

	/* NOTE: Saving this to implement JSON loading later - LevelLoader.cpp line 27 causes an error that will need to be resolved.
	auto fileUtils = FileUtils::getInstance();

	// Set the design resolution with the NO_BORDER policy.
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	cocos2d::Size frameSize = glview->getFrameSize();
	std::vector<std::string> searchPath;

	// Here, we select the most appropriate resource (i.e. image set) according to the actual frame height of the device.
	// If the resource (image) size is different from design resolution size, we need to set content scale factor.
	// This will either scale the images up or down to match the design resolution size.
	// The content scale factor is the ratio of the resource's height to the height of design resolution.

	// if the frame's height is larger than the height of medium resource size, select large resource.
	float scaleFactor = 1.0f;
	if (frameSize.height > mediumResolution.size.height) {
		searchPath.push_back(largeResolution.directory);
		scaleFactor = largeResolution.size.height / designResolutionSize.height;
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallResolution.size.height) {
		searchPath.push_back(mediumResolution.directory);
		scaleFactor = mediumResolution.size.height / designResolutionSize.height;
	}
	// if the frame's height is smaller than the height of medium resource size, select small resource.
	else {
		searchPath.push_back(smallResolution.directory);
		scaleFactor = smallResolution.size.height / designResolutionSize.height;
	}

	director->setContentScaleFactor(1);
	// Need to add our "data" path too.
	searchPath.push_back("data");
	fileUtils->setSearchPaths(searchPath);

	// Create the GameData singleton.
	m_ptr = GameData::sharedGameData();
	// Create the level loader object to load general game data.
	LevelLoader loader("data/GeneralGameData.json");

	// Set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// Run
	auto scene = MainMenu::createScene();
	director->runWithScene(scene);

	return true;
	*/
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
