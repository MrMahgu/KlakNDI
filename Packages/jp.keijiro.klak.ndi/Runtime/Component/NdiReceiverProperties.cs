using UnityEngine;

namespace Klak.Ndi {

public sealed partial class NdiReceiver : MonoBehaviour
{
    #region NDI source settings

    [SerializeField] string _ndiName = null;

    public string ndiName
      { get => _ndiName;
        set { _ndiName = value; Restart(); } }

    #endregion

    #region Target settings

    [SerializeField] RenderTexture _targetTexture = null;

    public RenderTexture targetTexture
      { get => _targetTexture;
        set => _targetTexture = value; }

    [SerializeField] Renderer _targetRenderer = null;

    public Renderer targetRenderer
      { get => _targetRenderer;
        set => _targetRenderer = value; }

    [SerializeField] string _targetMaterialProperty = null;

    public string targetMaterialProperty
      { get => _targetMaterialProperty;
        set => _targetMaterialProperty = value; }

    #endregion

    #region Blit Material settings

    [SerializeField] Material _sourceBlitMaterial = null;

    public Material sourceBlitMaterial
      { get => _sourceBlitMaterial;
        set => _sourceBlitMaterial = value; }
        
    [SerializeField] RenderTexture _targetBlitTexture = null;

    public RenderTexture targetBlitTexture
      { get => _targetBlitTexture;
        set => _targetBlitTexture = value; }
        
    #endregion

    #region Runtime property

    public RenderTexture texture => _converter?.LastDecoderOutput;

    public string metadata { get; set; }

    public Interop.Recv internalRecvObject => _recv;

    #endregion

    #region Resources asset reference

    [SerializeField, HideInInspector] NdiResources _resources = null;

    public void SetResources(NdiResources resources)
      => _resources = resources;

    #endregion
}

}
