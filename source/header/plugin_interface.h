/****************************************************************************
**
** Copyright (C) 2017, Henry van Merode
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef __OGAM_PLUGIN_INTERFACE_H__
#define __OGAM_PLUGIN_INTERFACE_H__

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "prerequisites.h"

/****************************************************************************
 Some statics
 ***************************************************************************/
static const std::string PLUGIN_TYPE_RESOURCE = "plugin_resource_type";
static const std::string PLUGIN_TYPE_MEDIA_WIDGET = "plugin_media_widget_type";

/****************************************************************************
 Structure of the meta data used by the plugins
 ***************************************************************************/
struct _OgamExport AssetMetaData
{
    /* General asset properties. These properties define the characteristics of an asset. Because of the plugin architecture of Ogam,
     * some of the AssetMetaData properties may or may not be used.
     * TODO: Define which properties are mandatory; these are the properties used in Ogam itself.
     *
     */
    std::string origin;                                         // Identification of the resource plugin
    double assetId;                                             // Identification of the asset; e.g. a database key
    std::string topLevelPath;                                   // Contains the top level path
    std::string path;                                           // Contains the path of the asset
    std::string baseNameOrReference;                            // Contains the (file) name of the asset
    std::string fullQualifiedFileNameOrReference;               // Refers to a location of the asset (e.g. path+filename)
    std::string extension;                                      // The extension is used to define the media type of the asset and to derive the media widget plugin
                                                                // is involved with creation of a media widget. Note, that the extension is without leading dot.
                                                                // Even if the baseNameOrReference does not have an extension, it must still be provided, otherwise a
                                                                // default media widget is used in the application.
                                                                // Examples: "jpg", " fbx", "mesh", "mp3", ...
    tm dateTimeAssetCreation;                                   // Timestamp when the asset was created; this is always GMT
    tm dateTimeModified;                                        // Latest timestamp when the asset was modified; this is always GMT
    long byteSize;                                              // Size of the asset in bytes

    // Locking properties
    tm dateTimeAssetLock;                                       // Timestamp indicating when the asset has been locked; this is always GMT
    std::string lockedByUser;                                   // Identification of the user that currently locks the resource

    // Properties, specific to the type of asset
    // TODO:
    // Images: dimensions, resolution, bitDepth
    // Audio: codec, sampleRate bitsPerSample, duration, channels (mono/stereo)
    // 3d models: numberOfVertices, numberOfIndices, hasNormals, hasTangents, hasUVs, hasAnimation
    // Video: codec, dimensions, frameRate, bitRate, bitDepth
    // Fonts:
    // Presentations:

    // Additional properties
    // TODO: E.g. Licenses, tags, description,
    std::vector <std::string> tags;                             // An asset may contain [0..n] tags; used for searching
    std::map <std::string, std::string> additionalProperties;   // Key/value pairs with custom properties
};

/****************************************************************************
 Defines the interface of a plugin.
 ***************************************************************************/
class _OgamExport PluginInterface
{
    public:
        PluginInterface() {}
        virtual ~PluginInterface() {}

        /** Get the type of the plugin.
        @remarks Ogam is capable of loading libraries with different plugin types
        */
        virtual const std::string& getType (void) const = 0;

        /** Get the name of the plugin. 
        @remarks An implementation must be supplied for this method to uniquely
            identify the plugin.
        */
        virtual const std::string& getName (void) const = 0;

        /** Perform the plugin initial installation sequence.
        @remarks An implementation must be supplied for this method. It must perform
        the startup tasks necessary to install any rendersystem customisations 
        or anything else that is not dependent on system initialisation, ie
        only dependent on the core of Ogre. It must not perform any
        operations that would create rendersystem-specific objects at this stage,
        that should be done in initialise().
        */
        virtual void install (void) = 0;

        /** Perform any tasks the plugin needs to perform on full system
            initialisation.
        @remarks An implementation must be supplied for this method. It is called 
            just after the system is fully initialised (either after Root::initialise
            if a window is created then, or after the first window is created)
            and therefore all rendersystem functionality is available at this
            time. You can use this hook to create any resources which are 
            dependent on a rendersystem or have rendersystem-specific implementations.
        */
        virtual void initialise (void) = 0;

        /** Perform any tasks the plugin needs to perform when the system is shut down.
        @remarks An implementation must be supplied for this method.
        This method is called just before key parts of the system are unloaded, 
        such as rendersystems being shut down. You should use this hook to free up 
        resources and decouple custom objects from the OGRE system, whilst all the
        instances of other plugins (e.g. rendersystems) still exist.
        */
        virtual void shutdown (void) = 0;

        /** Perform the final plugin uninstallation sequence. 
        @remarks An implementation must be supplied for this method. It must perform
        the cleanup tasks which haven't already been performed in shutdown()
        (e.g. final deletion of custom instances, if you kept them around incase
        the system was reinitialised). At this stage you cannot be sure what other
        plugins are still loaded or active. It must therefore not perform any
        operations that would reference any rendersystem-specific objects - those
        should have been sorted out in the 'shutdown' method.
        */
        virtual void uninstall (void) = 0;

        /** If the plugin has widgets and the resetWindowLayout function is called,
         the plugin should arrange its widgets to the default state.
         */
        virtual void resetWindowLayout (void) = 0;
    };

#endif
